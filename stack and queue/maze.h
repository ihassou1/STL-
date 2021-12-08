#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "position.h"

class Maze {
  public:
    /**
     * Creates a Maze of the specified size.  Initially, all spaces
     * are assumed to contain no walls. The upper-left corner is at
     * position (0,0), with Y increasing toward the bottom edge of the
     * map.
     */
    Maze(int width, int height);
    /**
     * Cleans up the memory used by a Maze.
     */
    ~Maze();
    /**
     * Retrieves the width of the map.
     * @return The width of this map.
     */
    int getWidth();
    /**
     * Retrieves the height of the map.
     * @return The height of this map.
     */
    int getHeight();
    /**
     * Determines if a given position contains a wall.
     * @param x The X coordinate of the position.
     * @param y The Y coordinate of the position.
     * @return true if there is wall in that place; false if there is not.
     */
    bool isWall(int x, int y);
    /**
     * Sets the specified location to be a wall.  The upper-left
     * corner is at position (0,0), with Y increasing toward the
     * bottom edge of the map.
     */
    void setWall(int x, int y);
    /**
     * Solves this Maze using a breadth-first search.
     * @return The path of positions which give a correct answer to the
     *         maze.  It is the caller's responsibility to delete this
     *         object.  If no path exists, nullptr will be returned.
     */
    List<Position*>* solveBreadthFirst();
    /**
     * Solves this Maze using a depth-first search.
     * @return The path of positions which give a correct answer to the
     *         maze.  It is the caller's responsibility to delete this
     *         object.  If no path exists, nullptr will be returned.
     */
    List<Position*>* solveDepthFirst();

private:
    /**
     * A utility method which creates and returns a list of the valid
     * neighbors of a given position.  A neighbor is a horizontally or
     * vertically adjacent space which is within the bounds of the
     * map.  For instance, consider the space in the map below marked
     * with an X:
     *
     *     ..#.
     *     .##X
     *     ....
     *
     * The X-marked space above has three neighbors: the one above,
     * the one below, and the one to the left.  The space to the right
     * is out of bounds and so would not be included in the returned
     * list. You can decide if you want to return the neighbors that
     * are walls or not, it is up to you. Make sure you program the
     * functions that call getNeighbors accordingly.
     *
     * @param position The position for which neighbors should be
     * found.
     * @return A new list of pointers to this position's
     * neighbors.  The caller assumes responsibility for deleting this
     * list.
     */
    List<Position*>* getNeighbors(Position* position);

    /**
     * A utility method which, given an OrderedCollection, will
     * perform a search using that collection to store unvisited
     * Positions.  This is the method where most of your work will be
     * done; solveBreadthFirst and solveDepthFirst should both call
     * this method.  @param exploration The data structure which will
     * be used to hold the unexplored positions during the search.
     * @return The path of positions which give the correct answer to
     * the maze.  It is the caller's responsibility to delete this
     * object.  If no path exists, nullptr will be returned.
     */
    List<Position*>* solve(OrderedCollection<Position*>* exploration);

    /** A dynamically-allocated two-dimenstional array of pointers to
        Position objects representing the maze. */
    Position*** positions;

    int width;
    int height;

  private:
    // You can safely ignore the following code.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
    Maze(const Maze& other) = delete;
    Maze& operator=(const Maze& other) = delete;
};
