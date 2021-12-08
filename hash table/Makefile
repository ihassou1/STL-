# Configure compiler settings
CXX=clang++
CXXFLAGS=-g -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the program.
OFILES = scrabbleAssistant.o hashFunctions.o
TESTS_OFILES = tests.o testScrabbleAssistant.o testHashTable.o testLinearDictionary.o

# The header files for the program
HFILES = $(shell ls -1 *.h)

#common executable dependencies
DEPS = $(HFILES) $(OFILES)

# UnitTest++ keeps its object files in this library.
UNITTEST_LIB = -lUnitTest++

all: scrabbleAssistant tests manualTests

# This target builds your main program.
scrabbleAssistant:  $(DEPS) main.o
	$(CXX) $(CXXFLAGS) -o $@ main.o $(OFILES)

# This target builds your tests.
tests: $(TESTS_OFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(TESTS_OFILES) $(OFILES) $(UNITTEST_LIB)

# This target builds your manual testing program.
manualTests: manualTests.o $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ manualTests.o $(OFILES)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp $(HFILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target deletes the temporary files we have built.
.PHONY: clean
clean:
	rm -f *.o
	rm -f scrabbleAssistant
	rm -f tests
	rm -f manualTests
