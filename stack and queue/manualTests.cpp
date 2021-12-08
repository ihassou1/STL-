/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

// TODO: put #includes here
#include "mazeUtils.h"
#include "maze.h"

using namespace std;

int main() {
    // TODO: write any tests you want here; this is your sandbox
    Maze* ourMaze = loadMap("test_data/big3.map");
    //cout << "width:" << ourMaze->getWidth() << endl;
    //cout << "height;" << ourMaze->getHeight() << endl;
    //string neighbors = renderAnswer(ourMaze, ourMaze->getNeighbors(new Position(4,1)));
    //string maze_string = renderAnswer(ourMaze, nullptr);
    List<Position*>* path = ourMaze->solveBreadthFirst();
    string solution = renderAnswer(ourMaze, path);
    //cout << solution << endl;
    delete ourMaze;
    delete path;
    //cout << neighbors;
    return 0;
}
