/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include <UnitTest++/UnitTest++.h>

#include "adts/list.h"
#include "maze.h"
#include "mazeUtils.h"

using namespace std;

#include <cmath>
#include <sstream>

/**
 * Veritifes that two positions are adjacent.
 */
void checkAdjacent(Position* p1, Position* p2) {
    int dx = abs(p1->getX() - p2->getX());
    int dy = abs(p1->getY() - p2->getY());
    if (dx + dy != 1) {
        stringstream ss;
        ss << "Positions are not adjacent (" << p1->getX() << "," << p1->getY()
           << ") vs. (" << p2->getX() << "," << p2->getY() << ")";
        CHECK_EQUAL("Positions are adjacent", ss.str());
    }
}

/**
 * Verifies the provided answer under the assumption that the maze has at
 * least one answer.
 */
void validateAnswer(Maze* maze, List<Position*>* answer) {
    CHECK(answer != nullptr);
    if (answer == nullptr) {
        return;
    }
    CHECK(answer->getSize() > 0);
    if (answer->getSize() <= 0) {
        return;
    }
    for (int i = 0; i < answer->getSize() - 1; i++) {
        checkAdjacent(answer->get(i), answer->get(i + 1));
    }
    for (int i = 0; i < answer->getSize(); i++) {
        Position* p = answer->get(i);
        CHECK_EQUAL(false, maze->isWall(p->getX(), p->getY()));
    }
    Position* start = answer->get(0);
    CHECK_EQUAL(0, start->getX());
    CHECK_EQUAL(0, start->getY());
    Position* end = answer->get(answer->getSize() - 1);
    CHECK_EQUAL(maze->getWidth() - 1, end->getX());
    CHECK_EQUAL(maze->getHeight() - 1, end->getY());
}

TEST(loads_properly) {
    // This test verifies that the Maze implementation loads properly.
    // The load_map function does the real work, but it's possible that the
    // Maze code didn't store the information correctly.
    Maze* maze = loadMap("test_data/example1.map");
    CHECK_EQUAL(5, maze->getWidth());
    CHECK_EQUAL(3, maze->getHeight());
    if (maze->getWidth() != 5 || maze->getHeight() != 3) {
        return;
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 5; x++) {
            bool shouldBeWall = ((x == 1 && y == 0) || (x == 1 && y == 1) ||
                                 (x == 3 && y == 0) || (x == 3 && y == 2));
            CHECK_EQUAL(shouldBeWall, maze->isWall(x, y));
        }
    }
    delete maze;
}

void testMapPossible(string name, int breadthAnswerSize) {
    Maze* maze = loadMap("test_data/" + name + ".map");
    List<Position*>* answer = maze->solveBreadthFirst();
    if (answer != nullptr) {
        validateAnswer(maze, answer);
        CHECK_EQUAL(breadthAnswerSize, answer->getSize());
        delete answer;
    } else {
        CHECK_EQUAL("solution", "no solution provided");
    }
    delete maze;

    maze = loadMap("test_data/" + name + ".map");
    answer = maze->solveDepthFirst();
    if (answer != nullptr) {
        validateAnswer(maze, answer);
        delete answer;
    } else {
        CHECK_EQUAL("solution", "no solution provided");
    }
    delete maze;
}

void testMapImpossible(string name) {
    Maze* maze = loadMap("test_data/" + name + ".map");
    List<Position*>* answer = maze->solveBreadthFirst();
    CHECK_EQUAL((List<Position*>*)nullptr, answer);
    if (answer != nullptr) {
        delete answer;
    }
    delete maze;

    maze = loadMap("test_data/" + name + ".map");
    answer = maze->solveDepthFirst();
    CHECK_EQUAL((List<Position*>*)nullptr, answer);
    if (answer != nullptr) {
        delete answer;
    }
    delete maze;
}

TEST(easyPossibleIn3) {
    testMapPossible("easy", 3);
}

TEST(example1PossibleIn9) {
    testMapPossible("example1", 9);
}

TEST(example2PossibleIn14) {
    testMapPossible("example2", 14);
}

TEST(example3PossibleIn11) {
    testMapPossible("example3", 11);
}

TEST(example4PossibleIn15) {
    testMapPossible("example4", 15);
}

TEST(example5PossibleIn17) {
    testMapPossible("example5", 17);
}

TEST(impossible1Impossible) {
    testMapImpossible("impossible1");
}

TEST(impossible2Impossible) {
    testMapImpossible("impossible2");
}

TEST(impossible3Impossible) {
    testMapImpossible("impossible3");
}

TEST(cyclePossibleIn9) {
    testMapPossible("cycle", 9);
}

TEST(big1PossibleIn175) {
    testMapPossible("big1", 175);
}

TEST(big2PossibleIn439) {
    testMapPossible("big2", 439);
}

TEST(big3PossibleIn1056) {
    testMapPossible("big3", 1056);
}

TEST(impossible4Impossible) {
    testMapImpossible("impossible4");
}

TEST(depthCheck1PossibleIn8) {
    testMapPossible("depthCheck1", 8);
}

TEST(depthCheck2PossibleIn8) {
    testMapPossible("depthCheck2", 8);
}

TEST(actuallyDepthFirst) {
    // The above tests establish (with high confidence) that the Maze is
    // using breadth-first search when we ask it to (because, on some of these
    // maps, the length of the depth-first search is longer than the shortest
    // path for any consistent ordering of node explorations).  But we don't
    // have a good way of making sure that the Maze is performing a
    // depth-first search.  Here, we'll accomplish that by creating two
    // different mazes; the first coincides with the shortest path if we
    // consider going right first and the second coincides if we go down first.
    // If the Maze class picks a consistent ordering, then at least one of
    // these mazes should yield a depth-first traversal which does not
    // match the breadth-first traversal.
    Maze* depth1 = loadMap("test_data/depthCheck1.map");
    List<Position*>* answer1 = depth1->solveDepthFirst();
    if (answer1 == nullptr) {
        delete depth1;
        CHECK_EQUAL("depthCheck1.map is solvable", "no solution");
        return;
    }
    Maze* depth2 = loadMap("test_data/depthCheck2.map");
    List<Position*>* answer2 = depth2->solveDepthFirst();
    delete depth1;
    delete depth2;
    if (answer1 == nullptr) {
        delete answer2;
        CHECK_EQUAL("depthCheck2.map is solvable", "no solution");
        return;
    }
    int len1 = answer1->getSize();
    int len2 = answer2->getSize();
    delete answer1;
    delete answer2;
    CHECK(len1 > 8 || len2 > 8);
}

int main() {
    return UnitTest::RunAllTests();
}
