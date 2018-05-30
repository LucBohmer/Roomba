#include "SerialLink.h"

std::mutex SerialLink::read_mtx_{};
std::mutex SerialLink::write_mtx_{};

/**
 *  \brief SerialLink::SerialLink starts a communication with an external device at a certain baud rate
 *  \param comPort is a std::string containing the 'name' of the port ('/dev/...')
 *  \param baud is of type unsigned int and contains the selected baudrate of the device
 **/
SerialLink::SerialLink(const std::string& comPort, 
                       const unsigned int baud, 
                       const unsigned int character_size, 
                       const boost::asio::serial_port_base::parity::type parity,
                       const boost::asio::serial_port_base::stop_bits::type stop_bits,
                       const boost::asio::serial_port_base::flow_control::type flow_control):
    comPort_{comPort}, baud_{baud}, io_{}, port_{io_} {
    
    //Catch file not found exception that might be thrown if the device is not connected
    try {
        port_.open(comPort_);
    }
    catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
        return;
    }

    //Check whether the port is open or not
    if (port_.is_open()) {
        //Set all the options for the serial link
        port_.set_option(boost::asio::serial_port_base::baud_rate(baud));
        port_.set_option(boost::asio::serial_port_base::character_size(character_size));
        port_.set_option(boost::asio::serial_port_base::parity(parity));
        port_.set_option(boost::asio::serial_port_base::stop_bits(stop_bits));
        port_.set_option(boost::asio::serial_port_base::flow_control(flow_control));
    }
    else {
        std::cerr << "ERROR: Serial port couldn't be opened\n";
        return;
    }
}

/**
 *  \brief SerialLink::~SerialLink closes the serial port if it is still open
 **/
SerialLink::~SerialLink() {
    if (port_.is_open()) {
        port_.close();
    }
}

/**
 *  \brief SerialLink::write writes data to the connected device
 *  \param dat is an array containing the data to send through the serial interface
 **/
void SerialLink::write(const std::vector<uint8_t>& dat) {
    if (dat.empty()) {
        std::cerr << "WARNING: Trying to write an empty buffer over the serial link\n";
        return;
    }
    try {
        std::lock_guard<std::mutex> lock{write_mtx_};
        boost::asio::write(port_, boost::asio::buffer(dat));
        //port_.write_some(boost::asio::buffer(dat));
    }
    catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
}

/**
 *  \brief SerialLink::read reads data from the serial devie
 *  \param dat is a vector that will be used to store the data
 *  \param read_size is of type size_t and determines the size of the data to be read
 **/
void SerialLink::read(std::vector<uint8_t>& dat, const size_t read_size) {
    try {
        dat.resize(read_size);
        std::lock_guard<std::mutex> lock{read_mtx_};
        boost::asio::read(port_, boost::asio::buffer(dat, read_size));
        //port_.read_some(boost::asio::buffer(dat, read_size));
    }
    catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
}

void SerialLink::readWrite(const std::vector<uint8_t>& data_out, std::vector<uint8_t>& data_in, const size_t read_size) {
    write(data_out);
    read(data_in, read_size);
}

