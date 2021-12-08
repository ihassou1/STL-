# Configure compiler settings
CXX=clang++
CXXFLAGS=-g -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the program.
OFILES = asciimationFunctions.o
# The header files for the program
HFILES = $(shell ls -1 *.h)

# UnitTest++ library needed for linking.
UNITTEST_LIB = -lUnitTest++

# A special target to build everything
all: asciimation tests manualTests

# This target builds your main program.
asciimation: $(HFILES) $(OFILES) asciimation.o
	$(CXX) $(CXXFLAGS) -o $@ asciimation.o $(OFILES)

# This target builds your tests.
tests: tests.o $(HFILES) $(OFILES)
	$(CXX) $(CXXFLAGS) -o $@ tests.o $(OFILES) $(UNITTEST_LIB)

# This target builds your manual testing program.
manualTests: manualTests.o $(HFILES) $(OFILES)
	$(CXX) $(CXXFLAGS) -o $@ manualTests.o $(OFILES)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp $(HFILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target deletes the temporary files we have built.
.PHONY: clean all
clean:
	rm -f *.o
	rm -f asciimation
	rm -f tests
	rm -f manualTests
