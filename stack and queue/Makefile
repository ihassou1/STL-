# Configure compiler settings
CXX=clang++
CXXFLAGS=-g -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the program.
OFILES = position.o maze.o mazeUtils.o
# The header files for the program
HFILES = $(shell ls -1 *.h)
# UnitTest++ keeps its object files in this directory.
UNITTEST_LIB = -lUnitTest++

all: maze testMaze testStackQueue manualTests

# This target builds your main program.
maze: $(HFILES) $(OFILES) main.o
	$(CXX) $(CXXFLAGS) -o $@ main.o $(OFILES)

# This target builds your tests for maze.
testMaze: testMaze.o $(HFILES) $(OFILES)
	$(CXX) $(CXXFLAGS) -o $@ testMaze.o $(OFILES) $(UNITTEST_LIB)

# This target builds your tests for stacks and queues.
testStackQueue: testStackQueue.o $(HFILES) $(OFILES)
	$(CXX) $(CXXFLAGS) -o $@ testStackQueue.o $(OFILES) $(UNITTEST_LIB)

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
	rm -f maze
	rm -f testMaze
	rm -f testStackQueue
	rm -f manualTests
