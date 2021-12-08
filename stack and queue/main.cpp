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

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3){
      throw runtime_error("usage : ./maze filename (breadth or depth)");
    }
    string fileName=argv[1];
    string searchAlgorithm =argv[2];
    if (searchAlgorithm!="breadth" && searchAlgorithm!="depth" ){
      throw runtime_error("second command line argument must be 'depth' or 'breadth' ");
    }
    Maze* ourMaze ;
    try {
        ourMaze =loadMap(fileName);
    } catch (runtime_error e){
      throw runtime_error("invalid maze file");
    }
    string path;
    if (searchAlgorithm=="breadth"){
      if (ourMaze->solveBreadthFirst()==nullptr){
        path="no solution path";
      }
      else{
        path=renderAnswer(ourMaze,ourMaze->solveBreadthFirst());
      }
    }
    else{
      if (ourMaze->solveDepthFirst()==nullptr){
        path="no solution path";
      }
      else{
        path=renderAnswer(ourMaze,ourMaze->solveDepthFirst());  
      }
    }
    std::cout << path << '\n';
    return 0;
}
