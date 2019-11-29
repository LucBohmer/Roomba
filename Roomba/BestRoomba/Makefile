CCXX = g++
INCLUDING = -I ../_libMQTT -I ../_libUtils -I ../_libSenseHAT -I ../roombaIO -I ../_libUtils/SerialLink -I ../RoombaMQTT
CXXFLAGS = -std=c++11 -Wall -Weffc++ -Os $(INCLUDING) \
           -D_GLIBCXX_USE_NANOSLEEP \
                          -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 \
                          -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 \
                          -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 \
                          -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
LDFLAGS = -lmosquittopp -L/usr/local/lib  -lm -pthread

EXECUTABLE = BestRoomba
SOURCES := ${wildcard *.cpp} \
	${wildcard ../_libMQTT/*.cpp} \
	${wildcard ../_libSenseHAT/*.c} \
	${wildcard ../_libUtils/*.c} \
	${wildcard ../_libUtils/SerialLink/*.cpp} \
	${wildcard ../RoombaMQTT/*.cpp}
HEADERS := ${wildcard *.h} \
	${wildcard ../roombaIO/*.h} \
	${wildcard ../_libMQTT/*.h} \
	${wildcard ../_libUtil/*.h} \
	${wildcard ../_libSenseHAT/*.h} \
	${wildcard ../_libUtils/SerialLink/*.h} \
	${wildcard ../RoombaMQTT/*.h} 
OBJECTS := ${SOURCES:.cpp=.o}
OBJECTS := ${OBJECTS:.c=.o}

${OUTPUT}: ${SRC}
	${COMPILER} ${FLAGS} -03 ${SRC} ${INC} -o ${OUTPUT}

.PHONY: all
all: ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file compiler option -MM
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM  $^ > $@

-include depend

# Buildnumber in text file
buildnumber.num: $(OBJECTS)
	@echo
	@echo "-- Sources: " $(SOURCES)
	@echo
	@if ! test -f buildnumber.num; then echo 0 > buildnumber.num; fi
	@echo $$(($$(cat buildnumber.num)+1)) > buildnumber.num

# Create a clean environment
.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

# Clean up dependency file
.PHONY: clean-depend
clean-depend: clean
	$(RM) depend
