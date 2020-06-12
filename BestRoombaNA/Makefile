CXX = g++
INCLUDING = #-I../_libMQTT -I../RoombaMQTT -I../_libUtils/SerialLink
#INCLUDING = SerialLinkAS.h
CXXFLAGS = -std=c++11 -Wall -Wextra -Weffc++ -Os $(INCLUDING) \
           -D_GLIBCXX_USE_NANOSLEEP \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
LDFLAGS = -L/usr/local/lib -pthread -lboost_system

EXECUTABLE = BestRoombaNA
SOURCES = ${wildcard *.cpp} \
		  ${wildcard ../_libUtils/SerialLink/*.cpp} \
		  ${wildcard ../I-O/*.cpp}
#          ${wildcard ../_libMQTT/*.cpp}
#          ${wildcard ../RoombaMQTT/*.cpp}
HEADERS = ${wildcard *.h} \
		  ${wildcard ../_libUtils/SerialLink/*.h} \
		  ${wildcard ../I-O/*.h}
#          ${wildcard ../_libMQTT/*.h} 
#          ${wildcard ../RoombaMQTT/*.h}
OBJECTS = ${SOURCES:.cpp=.o}

.PHONY: all
all: ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file using the compiler option -MM
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM  $^ > $@

-include depend

# Buildnumber in text file
buildnumber.num: $(OBJECTS)
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
