/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

LinkedList<int>* createListForward(int size) {
    LinkedList<int>* list = new LinkedList<int>();
    for (int i = 0; i < size; i++) {
        list->insertLast(i * 2);
    }
    list->checkInvariants();
    return list;
}

LinkedList<int>* createListBackward(int size) {
    LinkedList<int>* list = new LinkedList<int>();
    for (int i = size - 1; i >= 0; i--) {
        list->insertFirst(i * 2);
    }
    list->checkInvariants();
    return list;
}

TEST(createList) {
    LinkedList<int> list;
    list.checkInvariants();
}

TEST(addHeadAndRetrieve) {
    LinkedList<int> list;
    list.insertFirst(4);
    CHECK_EQUAL(4, list.getFirst());
    list.checkInvariants();
}

TEST(addHeadTwiceAndRetrieve) {
    LinkedList<int> list;
    list.insertFirst(4);
    list.insertFirst(5);
    CHECK_EQUAL(5, list.getFirst());
    list.checkInvariants();
}

TEST(addHeadTwiceAndRetrieveTail) {
    LinkedList<int> list;
    list.insertFirst(4);
    list.insertFirst(5);
    CHECK_EQUAL(4, list.getLast());
    list.checkInvariants();
}

TEST(addTailTwiceAndRetrieveHead) {
    LinkedList<int> list;
    list.insertLast(4);
    list.insertLast(5);
    CHECK_EQUAL(4, list.getFirst());
    list.checkInvariants();
}

TEST(addHeadThriceAndSize) {
    LinkedList<int>* list = createListBackward(3);
    CHECK_EQUAL(3, list->getSize());
    delete list;
}

TEST(addTailThriceAndSize) {
    LinkedList<int>* list = createListForward(3);
    CHECK_EQUAL(3, list->getSize());
    delete list;
}

TEST(addHeadManyAndGetEach) {
    LinkedList<int>* list = createListBackward(100);
    for (int i = 0; i < 100; i++) {
        CHECK_EQUAL(i * 2, list->get(i));
    }
    CHECK_EQUAL(100, list->getSize());
    delete list;
}

TEST(addTailManyAndGetEach) {
    LinkedList<int>* list = createListForward(100);
    for (int i = 0; i < 100; i++) {
        CHECK_EQUAL(i * 2, list->get(i));
    }
    CHECK_EQUAL(100, list->getSize());
    delete list;
}

TEST(addHeadTwiceRemoveOnceCheckAndSize) {
    LinkedList<int> list;
    list.insertFirst(4);
    list.insertFirst(7);
    CHECK_EQUAL(2, list.getSize());
    CHECK_EQUAL(7, list.removeFirst());
    CHECK_EQUAL(1, list.getSize());
    CHECK_EQUAL(4, list.getFirst());
    list.checkInvariants();
}

TEST(addTailTwiceRemoveOnceCheckAndSize) {
    LinkedList<int> list;
    list.insertLast(4);
    list.insertLast(7);
    CHECK_EQUAL(2, list.getSize());
    CHECK_EQUAL(7, list.removeLast());
    CHECK_EQUAL(1, list.getSize());
    CHECK_EQUAL(4, list.getFirst());
    list.checkInvariants();
}

TEST(multipleAddsAndRemoves) {
    LinkedList<int> list; // []
    list.insertLast(4); // [4]
    list.insertLast(8); // [4,8]
    list.insertFirst(2); // [2,4,8]
    list.insertLast(6); // [2,4,8,6]
    CHECK_EQUAL(4, list.getSize());
    CHECK_EQUAL(2, list.getFirst());
    CHECK_EQUAL(6, list.getLast());
    CHECK_EQUAL(8, list.get(2));
    CHECK_EQUAL(2, list.removeFirst()); // [4,8,6]
    CHECK_EQUAL(3, list.getSize());
    CHECK_EQUAL(4, list.getFirst());
    CHECK_EQUAL(6, list.removeLast()); // [4,8]
    CHECK_EQUAL(2, list.getSize());
    list.insertFirst(5); // [5,4,8]
    CHECK_EQUAL(5, list.getFirst());
    CHECK_EQUAL(8, list.removeLast()); // [5,4]
    CHECK_EQUAL(4, list.removeLast()); // [5]
    CHECK_EQUAL(1, list.getSize());
    CHECK_EQUAL(5, list.getFirst());
    CHECK_EQUAL(5, list.getLast());
    list.checkInvariants();
}

TEST(multipleAddsAndRemovesThenCheckInvariants) {
    LinkedList<int> list; // []
    list.insertLast(4); // [4]
    list.insertLast(8); // [4,8]
    list.insertFirst(2); // [2,4,8]
    list.insertLast(6); // [2,4,8,6]
    CHECK_EQUAL(4, list.getSize());
    list.checkInvariants();
    CHECK_EQUAL(2, list.getFirst());
    CHECK_EQUAL(6, list.getLast());
    CHECK_EQUAL(8, list.get(2));
    CHECK_EQUAL(2, list.removeFirst()); // [4,8,6]
    CHECK_EQUAL(3, list.getSize());
    list.checkInvariants();
    CHECK_EQUAL(4, list.getFirst());
    CHECK_EQUAL(6, list.removeLast()); // [4,8]
    CHECK_EQUAL(2, list.getSize());
    list.checkInvariants();
    list.insertFirst(5); // [5,4,8]
    CHECK_EQUAL(5, list.getFirst());
    CHECK_EQUAL(8, list.removeLast()); // [5,4]
    CHECK_EQUAL(4, list.removeLast()); // [5]
    CHECK_EQUAL(1, list.getSize());
    list.checkInvariants();
    CHECK_EQUAL(5, list.getFirst());
    CHECK_EQUAL(5, list.getLast());
    list.checkInvariants();
}

TEST(emptyThenNonEmptyThenEmptyThenNonEmpty) {
    LinkedList<int> list;
    list.insertLast(2); // [2]
    list.insertLast(6); // [2,6]
    list.insertLast(3); // [2,6,3]
    CHECK(!list.isEmpty());
    CHECK_EQUAL(2, list.removeFirst()); // [6,3]
    CHECK_EQUAL(6, list.removeFirst()); // [3]
    CHECK_EQUAL(3, list.removeFirst()); // []
    CHECK(list.isEmpty());
    CHECK_EQUAL(0, list.getSize());
    list.insertLast(3); // [3]
    CHECK(!list.isEmpty());
    CHECK_EQUAL(1, list.getSize());
    CHECK_EQUAL(3, list.getFirst());
    CHECK_EQUAL(3, list.removeLast()); // []
    CHECK(list.isEmpty());
    CHECK_EQUAL(0, list.getSize());
    CHECK_THROW(list.get(0), std::runtime_error);
    list.insertFirst(5); // [5]
    CHECK(!list.isEmpty());
    CHECK_EQUAL(1, list.getSize());
    CHECK_EQUAL(5, list.get(0));
    list.checkInvariants();
}

TEST(emptyListExceptions) {
    LinkedList<int> list;
    CHECK_THROW(list.getFirst(), std::runtime_error);
    CHECK_THROW(list.getLast(), std::runtime_error);
    CHECK_THROW(list.removeFirst(), std::runtime_error);
    CHECK_THROW(list.removeLast(), std::runtime_error);
    CHECK_THROW(list.get(0), std::runtime_error);
    list.checkInvariants();
}

TEST(indexBoundsExceptions) {
    LinkedList<int> list;
    CHECK_THROW(list.get(0), std::runtime_error);
    list.insertFirst(5); // [5]
    CHECK_EQUAL(5, list.get(0));
    CHECK_THROW(list.get(1), std::runtime_error);
    CHECK_THROW(list.get(2), std::runtime_error);
    list.insertLast(4); // [5,4]
    CHECK_EQUAL(5, list.get(0));
    CHECK_EQUAL(4, list.get(1));
    CHECK_THROW(list.get(2), std::runtime_error);
    list.insertFirst(6); // [6,5,4]
    CHECK_EQUAL(6, list.get(0));
    CHECK_EQUAL(5, list.get(1));
    CHECK_EQUAL(4, list.get(2));
    CHECK_THROW(list.get(3), std::runtime_error);
    CHECK_THROW(list.get(-1), std::runtime_error);
    CHECK_THROW(list.get(-20), std::runtime_error);
    list.checkInvariants();
}

TEST(stringList) {
    LinkedList<string> list;
    CHECK(list.isEmpty());
    list.insertFirst("test"); // ["test"]
    CHECK_EQUAL("test", list.getFirst());
    CHECK_EQUAL("test", list.getLast());
    CHECK_EQUAL("test", list.get(0));
    list.insertLast("ing"); // ["test","ing"]
    CHECK_EQUAL("ing", list.getLast());
    CHECK_EQUAL("ing", list.get(1));
    CHECK_EQUAL("test", list.getFirst());
    CHECK_EQUAL("test", list.get(0));
    CHECK_EQUAL(2, list.getSize());
    list.checkInvariants();
}

TEST(performanceTestinsertFirstAndgetFirst) {
    cout << "Beginning performance test of insertFirst/getFirst..." << endl;
    LinkedList<int>* list = createListBackward(1000000);
    CHECK_EQUAL(0, list->getFirst());
    delete list;
    cout << "getFirst test complete." << endl;
}

TEST(performanceTestinsertFirstAndremoveFirst) {
    cout << "Beginning performance test of insertFirst/removeFirst..." << endl;
    LinkedList<int>* list = createListBackward(1000000);
    int i = 0;
    while (!list->isEmpty()) {
        CHECK_EQUAL(i * 2, list->removeFirst());
        i++;
    }
    delete list;
    cout << "removeFirst test complete." << endl;
}

TEST(performanceTestinsertFirstAndGetSize) {
    cout << "Beginning performance test of insertFirst/getSize..." << endl;
    LinkedList<int> list;
    for (int i = 0; i < 1000000; i++) {
        CHECK_EQUAL(i, list.getSize());
        list.insertFirst(i);
    }
    list.checkInvariants();
    cout << "getSize test complete." << endl;
}

int main() {
    return UnitTest::RunAllTests();
}
