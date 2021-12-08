#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/list.h"

// This file declares two classes: a LinkedListNode class (which represents a
// single node in a linked list) and a LinkedList class (which represents a
// full linked list as an implementation of the List ADT).

/**
 * This class represents a single node in a linked list.  It contains
 * one list element as well as pointers to the nodes which follow it
 * (or NULL when those nodes don't exist).
 * @tparam T The type of data stored in the list.
 */
template <typename T> class LinkedListNode {

  public:
    /**
     * Constructs a new node.
     * @param val The value to store in the node.
     * @param next An optional pointer to the following node.
     *             If unspecified next should be set to nullptr.
     */
    LinkedListNode<T>(T val, LinkedListNode<T>* next);

    // public data members:
    T value;
    LinkedListNode<T>* next;
};

/**
 * This class implements this list ADT as a linked list.
 * @tparam T The type of data stored in the list.
 */
template <typename T> class LinkedList : public List<T> {
  public:
    LinkedList();
    ~LinkedList();

    /**
     * Confirms that there are this->size elements in the list.
     * @throws runtime_error if the invariant does not hold.
     */
    void checkInvariants();

    // See list.h for comments on these methods:
    int getSize();
    bool isEmpty();
    T getFirst();
    T getLast();
    T get(int index);
    void insertFirst(T value);
    void insertLast(T value);
    T removeFirst();
    T removeLast();
  private:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    int size;
};

#include "linkedList-inl.h"
