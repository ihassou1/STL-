/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedQueue.h"
#include "adts/stlList.h"

using namespace std;

// NOTE: Most of the method bodies in this class will only require a
// single line of code!

template <typename T> LinkedQueue<T>::LinkedQueue() {
}

template <typename T> int LinkedQueue<T>::getSize() {
    return queueList.getSize();
}

template <typename T> bool LinkedQueue<T>::isEmpty() {
    return queueList.isEmpty();
}

template <typename T> T LinkedQueue<T>::peek() {
    return queueList.getFirst();
}

template <typename T> void LinkedQueue<T>::enqueue(T element) {
    queueList.insertLast(element);
}

template <typename T> T LinkedQueue<T>::dequeue() {
    return queueList.removeFirst();
}

template <typename T> void LinkedQueue<T>::insert(T element) {
    queueList.insertLast(element);
}

template <typename T> T LinkedQueue<T>::remove() {
    return queueList.removeFirst();
}
