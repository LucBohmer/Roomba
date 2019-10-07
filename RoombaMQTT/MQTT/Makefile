CXX = g++
INCLUDING = -I../../_libSenseHAT  -I../../_libMQTT -I../../_libUtils
CXXFLAGS = -std=c++14 -Wall -Weffc++ -Os $(INCLUDING) \
           -D_GLIBCXX_USE_NANOSLEEP \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 \
			  -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
LDFLAGS = -L/usr/local/lib -lmosquittopp -lm -pthread

EXECUTABLE = RoombaMQTTClient
SOURCES := ${wildcard *.cpp}
HEADERS := ${wildcard *.h}
OBJECTS := ${SOURCES:.cpp=.o}
OBJECTS := ${OBJECTS:.c=.o}

.PHONY: all
all: ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
	@echo
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
