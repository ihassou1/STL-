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
#include "linkedQueue.h"
#include "linkedStack.h"

using namespace std;

#include <cmath>
#include <sstream>

TEST(emptyQueue) {
    LinkedQueue<int> q;
}

TEST(singleElementQueue) {
    LinkedQueue<int> q;
    CHECK_EQUAL(0, q.getSize());
    q.enqueue(5);
    CHECK_EQUAL(1, q.getSize());
    CHECK_EQUAL(5, q.dequeue());
    CHECK_EQUAL(0, q.getSize());
}

TEST(multiElementQueue) {
    LinkedQueue<int> q;
    CHECK_EQUAL(0, q.getSize());
    q.enqueue(5);
    CHECK_EQUAL(1, q.getSize());
    q.enqueue(8);
    CHECK_EQUAL(2, q.getSize());
    q.enqueue(9);
    CHECK_EQUAL(3, q.getSize());
    CHECK_EQUAL(5, q.dequeue());
    CHECK_EQUAL(2, q.getSize());
    q.enqueue(4);
    CHECK_EQUAL(3, q.getSize());
    CHECK_EQUAL(8, q.dequeue());
    CHECK_EQUAL(2, q.getSize());
    CHECK_EQUAL(9, q.dequeue());
    CHECK_EQUAL(1, q.getSize());
    CHECK_EQUAL(4, q.dequeue());
    CHECK_EQUAL(0, q.getSize());
}

TEST(emptyStack) {
    LinkedStack<int> s;
}

TEST(singleElementStack) {
    LinkedStack<int> s;
    CHECK_EQUAL(0, s.getSize());
    s.push(5);
    CHECK_EQUAL(1, s.getSize());
    CHECK_EQUAL(5, s.pop());
    CHECK_EQUAL(0, s.getSize());
}

TEST(multiElementStack) {
    LinkedStack<int> s;
    CHECK_EQUAL(0, s.getSize());
    s.push(5);
    CHECK_EQUAL(1, s.getSize());
    s.push(8);
    CHECK_EQUAL(2, s.getSize());
    s.push(9);
    CHECK_EQUAL(3, s.getSize());
    CHECK_EQUAL(9, s.pop());
    CHECK_EQUAL(2, s.getSize());
    s.push(4);
    CHECK_EQUAL(3, s.getSize());
    CHECK_EQUAL(4, s.pop());
    CHECK_EQUAL(2, s.getSize());
    CHECK_EQUAL(8, s.pop());
    CHECK_EQUAL(1, s.getSize());
    CHECK_EQUAL(5, s.pop());
    CHECK_EQUAL(0, s.getSize());
}

TEST(orderedCollectionConformance) {
    OrderedCollection<int>* o = new LinkedStack<int>();
    o->insert(4);
    o->insert(5);
    CHECK_EQUAL(5, o->remove());
    CHECK_EQUAL(4, o->remove());
    delete o;
    o = new LinkedQueue<int>();
    o->insert(4);
    o->insert(5);
    CHECK_EQUAL(4, o->remove());
    CHECK_EQUAL(5, o->remove());
    delete o;
}


int main() {
    return UnitTest::RunAllTests();
}
