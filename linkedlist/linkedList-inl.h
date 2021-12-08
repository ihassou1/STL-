/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <iostream>
using namespace std;

using std::runtime_error;

// This file defines the methods for two classes: LinkedListNode and LinkedList.
// The LinkedListNode methods have been defined for you.  You are responsible
// for defining the LinkedList methods.

// //////// LinkedListNode /////////////////////////////////////////////////////

template <typename T>
LinkedListNode<T>::LinkedListNode(T val, LinkedListNode<T>* next) {
    this->value = val;
    this->next = next;
}

// //////// LinkedList /////////////////////////////////////////////////////////

template <typename T> LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template <typename T> LinkedList<T>::~LinkedList() {
    // if list is empty
    if (this->size == 0) {
        return;
    }
    LinkedListNode<T> *currentNode = this->head;
    LinkedListNode<T> *nextNode = this->head->next;
    while (nextNode != nullptr) {
        delete currentNode;
        currentNode = nextNode;
        nextNode = nextNode->next;
    }
    delete currentNode;
    currentNode = nullptr;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T> void LinkedList<T>::checkInvariants() {
    // if list is empty
    if (this->size == 0) {
        if (this->head != nullptr) {
            throw runtime_error("list is empty but head does not point to null");
        }
        if (this->tail != nullptr) {
            throw runtime_error("list is empty but tail does not point to null");
        }
        return;
    }
    // check if number of nodes is equal to size
    int count = 0;
    LinkedListNode<T> *currentNode = this->head;
    while (currentNode != nullptr) {
        count++;
        currentNode = currentNode->next;
    }
    if (count != this->size) {
        throw runtime_error("size is not equal to count");
    }

    // check if this->tail points to the last node
    currentNode = this->head;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    if (currentNode != this->tail) {
        throw runtime_error("this->tail does not point to the last node");
    }

    // check if empty list, this->head points to nullptr
    if (this->size == 0) {
        if (this->head != nullptr) {
            throw runtime_error("this->head does not point to nullptr");
        }
        if (this->tail != nullptr) {
            throw runtime_error("this->tail does not point to nullptr");
        }
    }
}

template <typename T> int LinkedList<T>::getSize() {
    return this->size;
}

template <typename T> bool LinkedList<T>::isEmpty() {
    return this->size == 0;
}

template <typename T> T LinkedList<T>::getFirst() {
    if (this->size == 0) {
        throw runtime_error("list is empty");
    }
    return this->head->value;
}

template <typename T> T LinkedList<T>::getLast() {
    if (this->size == 0) {
        throw runtime_error("list is empty");
    }
    LinkedListNode<T> *currentNode = this->head;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    return currentNode->value;
}

template <typename T> T LinkedList<T>::get(int index) {
    if (this->size == 0) {
        throw runtime_error("list is empty");
    }
    LinkedListNode<T> *currentNode = this->head;
    if (index < 0 || index >= this->size) {
        throw runtime_error("index out of bounds");
    }
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->value;
}

template <typename T> void LinkedList<T>::insertFirst(T value) {
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value, this->head);
    this->head = newNode;
    if (this->size == 0) {
        this->tail = newNode;
    }
    this->size++;
}

template <typename T> void LinkedList<T>::insertLast(T value) {
    LinkedListNode<T> *newNode = new LinkedListNode<T>(value, nullptr);
    if (this->tail != nullptr) {
        this->tail->next = newNode;
    }
    this->tail = newNode;
    if (this->size == 0) {
        this->head = newNode;
    }
    this->size++;
}

template <typename T> T LinkedList<T>::removeFirst() {
    if (this->size == 0) {
        throw runtime_error("list is empty");
    }
    T firstVal = this->head->value;
    if (this->size == 1) {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
    }
    else {
        LinkedListNode<T> *newHead = this->head->next;
        delete this->head;
        this->head = newHead;
        newHead = nullptr;
    }
    this->size--;
    return firstVal;
}

template <typename T> T LinkedList<T>::removeLast() {
    if (this->size == 0) {
        throw runtime_error("list is empty");
    }
    T lastVal = this->tail->value;
    if (this->size == 1) {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
        this->size--;
        return lastVal;
    }
    LinkedListNode<T> *currentNode = this->head;
    while (currentNode->next->next != nullptr) {
        currentNode = currentNode->next;
    }
    delete this->tail;
    this->tail = currentNode;
    currentNode->next = nullptr;
    this->size--;
    return lastVal;
}
