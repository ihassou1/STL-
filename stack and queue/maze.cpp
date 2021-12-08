/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

/* ADTs */
#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "adts/queue.h"
#include "adts/stack.h"

/* Implementations of above ADTs */
#include "adts/stlList.h"
#include "linkedQueue.h"
#include "linkedStack.h"

#include "maze.h"

using namespace std;

Maze::Maze(int width, int height) {
    this->width = width;
    this->height = height;
    this->positions = new Position**[width];
    for (int i=0; i<this->width; i++){
        this->positions[i] = new Position*[height];
        for (int j=0; j<this->height; j++){
            this->positions[i][j] = new Position(i,j);
        }
    }
}

Maze::~Maze() {
    for (int i=0; i<width; i++){
        for (int j=0; j<height; j++){
            delete this->positions[i][j];
            this->positions[i][j] = nullptr;
        }
        delete[] this->positions[i];
        this->positions[i] = nullptr;

    }
    delete[] this->positions;
    this->positions = nullptr;
}

int Maze::getWidth() {
    return this->width;
}

int Maze::getHeight() {
    return this->height;
}

bool Maze::isWall(int x, int y) {
    return this->positions[x][y]->isWall();
}

void Maze::setWall(int x, int y) {
    this->positions[x][y]->setWall();
}

List<Position*>* Maze::getNeighbors(Position* position) {
    int x = position->getX();
    int y = position->getY();
    List<Position*>* neighborsList = new STLList<Position*>;
    // if not wall and within bounds, add top neighbor
    if ( (y - 1) >= 0 && !this->positions[x][y - 1]->isWall() ) {
        neighborsList->insertLast(this->positions[x][y - 1]);
    }
    // if not wall and within bounds, add left neighbor
    if ( (x - 1) >= 0 && !this->positions[x - 1][y]->isWall() ) {
        neighborsList->insertLast(this->positions[x - 1][y]);
    }
    // if not wall and within bounds, add right neighbor
    if ( (x + 1) < this->width && !this->positions[x + 1][y]->isWall() ) {
        neighborsList->insertLast(this->positions[x + 1][y]);
    }
    // if not wall and within bounds, add bottom neighbor
    if ( (y + 1) < this->height && !this->positions[x][y + 1]->isWall() ) {
        neighborsList->insertLast(this->positions[x][y + 1]);
    }
    return neighborsList;
}

List<Position*>* Maze::solveBreadthFirst() {
    OrderedCollection<Position*>* queue = new LinkedQueue<Position*>;
    //List<Position*>* solutionPath = solve(queue);
    return solve(queue);
}

List<Position*>* Maze::solveDepthFirst() {
    OrderedCollection<Position*>* stack = new LinkedStack<Position*>;
    //List<Position*>* solutionPath = solve(stack);
    return solve(stack);
}

List<Position*>* Maze::solve(OrderedCollection<Position*>* exploration) {
    exploration->insert( this->positions[0][0] );
    this->positions[0][0]->setVisited();

    List<Position*>* neighborsList;

    while (!exploration->isEmpty()) {
        Position* currentPosition = exploration->remove();
        int currentX = currentPosition->getX();
        int currentY = currentPosition->getY();

        // if current position is exit, search is complete
        if (currentX == (this->width - 1) && currentY == (this->height - 1)) {
            break;
        }

        neighborsList = getNeighbors(currentPosition);

        // for each neighbor
        for ( int i=0; i<neighborsList->getSize(); i++ ) {
            Position* neighbor = neighborsList->get(i);
            if (!neighbor->isVisited()) {
                neighbor->setVisited();
                neighbor->setPrevious(currentPosition);
                exploration->insert(neighbor);
            }
        }

        delete neighborsList;
    }

    neighborsList = nullptr;
    delete exploration;

    // solution is never found
    if (this->positions[this->width - 1][this->height - 1]->isVisited() == false) {
        return nullptr;
    }

    // trace back to find solution path
    List<Position*>* solutionPath = new STLList<Position*>;
    Position* solutionNode = this->positions[this->width - 1][this->height - 1];
    while (solutionNode != nullptr) {
        solutionPath->insertFirst(solutionNode);
        solutionNode = solutionNode->getPrevious();
    }
    return solutionPath;
}
