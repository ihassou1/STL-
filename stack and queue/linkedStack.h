#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/stack.h"
#include "adts/stlList.h"

/**
 * The LinkedStack is an implementation of the Stack interface using a
 * linked list.
 * @tparam T The type of elements stored in the stack.
 */
template <typename T> class LinkedStack : public Stack<T> {
  public:
    LinkedStack();
    void push(T element);
    T pop();
    void insert(T element);
    T remove();
    int getSize();
    bool isEmpty();
    T peek();

  private:
    STLList<T> stackList;

  private:
    // You can safely ignore the following code.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
    LinkedStack(const LinkedStack& other) = delete;
    LinkedStack& operator=(const LinkedStack& other) = delete;
};

#include "linkedStack-inl.h"
