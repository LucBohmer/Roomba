INCLUDING = -I/home/iot/Roomba/_libMQTT -I/home/iot/Roomba/RoombaMQTT -I/home/iot/Roomba/_libUtils -I/home/iot/Roomba/_libSenseHAT -I/home/iot/Roomba/I-O 
CXXFLAGS = -std=c++14 -Wall -Wextra -Weffc++ -Os $(INCLUDING) \
	-D_GLIBCXX_USE_NANOSLEEP \
	-D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 \
	-D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 \
	-D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 \
	-D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 

LDFLAGS = -L/usr/local/lib -pthread -lboost_system -lm -lmosquittopp -lRTIMULib 

EXECUTABLE = BestRoombaNA 

SOURCES = ${wildcard *.cpp} \
	${wildcard /home/iot/Roomba/_libUtils/*.cpp} \
	${wildcard /home/iot/Roomba/_libUtils/SerialLink/*.cpp} \
	${wildcard /home/iot/Roomba/I-O/*.cpp} \
	${wildcard /home/iot/Roomba/_libSenseHAT/*.cpp} \
        ${wildcard /home/iot/Roomba/_libSenseHAT/*.c} \
	${wildcard /home/iot/Roomba/_libMQTT/*.cpp} \
	${wildcard /home/iot/Roomba/RoombaMQTT/*.cpp} 

HEADERS = ${wildcard *.h} \
	${wildcard /home/iot/Roomba/_libUtils/*.h} \
	${wildcard /home/iot/Roomba/_libUtils/SerialLink/*.h} \
	${wildcard /home/iot/Roomba/I-O/*.h} \
	${wildcard /home/iot/Roomba/_libSenseHAT/*.h} \
	${wildcard /home/iot/Roomba/_libMQTT/*.h} \
	${wildcard /home/iot/Roomba/RoombaMQTT/*.h} 

OBJECTS = ${SOURCES:.cpp=.o} 
OBJECTS = ${SOURCES:.c=.o} 

.PHONY: all 
all: ${EXECUTABLE} 

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@ -lRTIMULib
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file using the compiler option -MM
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $^ > $@ 

-include depend

# Buildnumber in text file
buildnumber.num: $(OBJECTS)
	@if ! test -f buildnumber.num; then echo 0 > buildnumber.num; fi
	@echo $$(($$(cat buildnumber.num)+1)) > buildnumber.num

# Create a clean environment
#.PHONY: clean 
#clean:
#	$(RM) $(EXECUTABLE) $(OBJECTS)

# Clean up dependency file
#.PHONY: clean-depend 
#clean-depend: clean
#	$(RM) depend
