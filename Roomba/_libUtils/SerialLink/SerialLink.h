#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <mutex>
#include <vector>
#include <iostream>
#include <type_traits>

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

/**
 *  \class SerialLink established a connection with an external serial device
 *  \note The serial link class uses the Asio library from Boost to write/read data
 **/
class SerialLink {
public:

    //Constructor(s) & Destructor
    SerialLink() = delete;
    SerialLink(const std::string& comPort, 
               const unsigned int baud, 
               const unsigned int character_size = 8, 
               const boost::asio::serial_port_base::parity::type parity = boost::asio::serial_port_base::parity::none,
               const boost::asio::serial_port_base::stop_bits::type stop_bits = boost::asio::serial_port_base::stop_bits::one,
               const boost::asio::serial_port_base::flow_control::type flow_control = boost::asio::serial_port_base::flow_control::none);
    ~SerialLink();

    //Getters
    inline std::string getComPort() const { return comPort_; }
    inline unsigned int getBaud() const { return baud_; }

    //Read & Write
    void write(const std::vector<uint8_t>& dat);
    void read(std::vector<uint8_t>& dat, const size_t read_size=1);
    void readWrite(const std::vector<uint8_t>& dat_out, std::vector<uint8_t>& dat_in, const size_t read_size=1);
private:
    //Communication related variables
    const std::string comPort_;
    const unsigned int baud_;
    boost::asio::io_service io_;
    boost::asio::serial_port port_;

    //Thread safety
    static std::mutex read_mtx_;
    static std::mutex write_mtx_;
};

#endif

