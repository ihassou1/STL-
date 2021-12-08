#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>

/**
 * This class represents data about a single position in a maze.  It
 * includes data for both the maze itself as well as the task of finding
 * a path through the maze.
 */
class Position {
  public:
    /**
     * Creates a new position representing the space at (x,y) in a maze.
     * This space is assumed to have no wall until we learn otherwise.
     */
    Position(int x, int y);

    /** Retrieve the X coordinate of this position. */
    int getX();
    /** Retrieve the Y coordinate of this position. */
    int getY();

    /** Mark current position as a wall. */
    void setWall();
    /** Return true if current position is a wall, and false otherwise. */
    bool isWall();

    /** Return true if position has been marked as visited. */
    bool isVisited();
    /** Set visited flag of position to true. */
    void setVisited();
    /** Clear visited flag of position by setting it to false. */
    void clearVisited();

    /**
     * Retrieves a pointer to the position previous to this one.
     * @return A pointer to the Position that first visited this Position.  If
     * no
     *         one has visited this Position yet, returns nullptr.
     */
    Position* getPrevious();
    /**
     * Sets the value of the previous pointer for this Position.
     */
    void setPrevious(Position* pos);

  private:
    /** The X coordinate of this position. */
    int x;
    /** The Y coordinate of this position. */
    int y;
    /** true if this position contains a wall; false if it does not. */
    bool wall;
    /** true if this position has been visited by the search; false if it has
        not. */
    bool visited;
    /** A search variable containing a pointer to the Position that we were in
        when we began exploring this one.  If we have not yet explored this
        position (or if this is the first position we explored), then this
        pointer is nullptr. */
    Position* previous;

  private:
    // You can safely ignore the following code.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
    Position(const Position& other) = delete;
    Position& operator=(const Position& other) = delete;
};
