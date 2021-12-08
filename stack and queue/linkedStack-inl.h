/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedStack.h"
#include "adts/stlList.h"

using namespace std;

// NOTE: Most of the method bodies in this class will only require a
// single line of code!

template <typename T> LinkedStack<T>::LinkedStack() {
}

template <typename T> void LinkedStack<T>::push(T element) {
    stackList.insertFirst(element);
}

template <typename T> T LinkedStack<T>::pop() {
    return stackList.removeFirst();
}

template <typename T> void LinkedStack<T>::insert(T element) {
  // To "insert" into a stack is to push onto it.  So when we are told to
  // insert, we will push.
   stackList.insertFirst(element);
}

template <typename T> T LinkedStack<T>::remove() {
    return stackList.removeFirst();
}

template <typename T> int LinkedStack<T>::getSize() {
    return stackList.getSize();
}

template <typename T> bool LinkedStack<T>::isEmpty() {
    return stackList.isEmpty();
}

template <typename T> T LinkedStack<T>::peek() {
    return stackList.getFirst();
}
