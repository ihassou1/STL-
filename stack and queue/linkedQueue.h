#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/queue.h"
#include "adts/stlList.h"

/**
 * The LinkedQueue is an implementation of the Queue interface using a
 * linked list.
 * @tparam T The type of elements stored in the queue.
 */
template <typename T> class LinkedQueue : public Queue<T> {
  public:
    LinkedQueue();
    void enqueue(T element);
    T dequeue();
    void insert(T element);
    T remove();
    int getSize();
    bool isEmpty();
    T peek();

  private:
    STLList<T> queueList;



  private:
    // You can safely ignore the following code.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
    LinkedQueue(const LinkedQueue& other) = delete;
    LinkedQueue& operator=(const LinkedQueue& other) = delete;
};

#include "linkedQueue-inl.h"
