/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>

#include "adts/list.h"
#include "adts/stlList.h"

using std::runtime_error;

template <typename K, typename V>
V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {
    if (current == nullptr) {
        throw runtime_error("key not found in subtree");
    }
    V value;
    if (current->getKey() == key) {
        value = current->getValue();
    }
    else if (current->getKey() > key) {
        value = findInSubtree(current->getLeft(), key);
    }
    else {
        value = findInSubtree(current->getRight(), key);
    }
    return value;
}

template <typename K, typename V>
bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {
    if (current == nullptr) {
        return false;
    }
    V value;
    if (current->getKey() == key) {
        return true;
    }
    else if (current->getKey() > key) {
        return containsInSubtree(current->getLeft(), key);
    }
    else {
        return containsInSubtree(current->getRight(), key);
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key,
    V value) {
    if (current == nullptr) {
      throw runtime_error("key not found in subtree");
    }
    if (current->getKey() == key) {
      current->setValue(value);
    }
    else if (current->getKey() > key) {
      updateInSubtree(current->getLeft(), key, value);
    }
    else {
      updateInSubtree(current->getRight(), key, value);
    }
}

template <typename K, typename V>
int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return -1;
    }
    int leftHeight = getHeightInSubtree(current->getLeft());
    int rightHeight = getHeightInSubtree(current->getRight());
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMinInSubtree(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        throw runtime_error("subtree is empty");
    }
    // no more left children, this is the min node
    if (current->getLeft() == nullptr) {
        pair<K, V> node = {current->getKey(), current->getValue()};
        return node;
    }
    return getMinInSubtree(current->getLeft());
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        throw runtime_error("subtree is empty");
    }
    // no more right children, this is the max node
    if (current->getRight() == nullptr) {
        pair<K, V> node = {current->getKey(), current->getValue()};
        return node;
    }
    return getMaxInSubtree(current->getRight());
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {
    if (current == nullptr) {
        LinkedBSTNode<K,V>* node = new LinkedBSTNode<K,V>(key, value);
        this->size++;
        return node;
    }
    // what we want to insert is greater than the current key, move to right
    if (current->getKey() < key) {
        current->setRight(insertInSubtree(current->getRight(), key, value));
    }
    // what we want to insert is less than the current key, move to left
    else if (current->getKey() > key) {
        current->setLeft(insertInSubtree(current->getLeft(), key, value));
    }
    else {
        throw runtime_error("key already exists in tree");
    }
    return current;
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {
    if (current == nullptr) {
        throw runtime_error("key not found in subtree");
    }
    if (current->getKey() == key) {
        this->size--;
        // if node is a leaf
        if (current->getRight() == nullptr && current->getLeft() == nullptr) {
            delete current;
            current = nullptr;
            return current;
        }
        // if node has one child on the right, make this the new root
        else if (current->getRight() == nullptr) {
            LinkedBSTNode<K, V>* temp = current->getLeft();
            delete current;
            return temp;
        }
        // if node has one child on the left, make this the new root
        else if (current->getLeft() == nullptr) {
            LinkedBSTNode<K, V>* temp = current->getRight();
            delete current;
            return temp;
        }
        // if node has two children
        else {
            pair<K, V> predecessor = getMaxInSubtree(current->getLeft());
            current->setLeft(removeFromSubtree(current->getLeft(), predecessor.first));
            current->setKey(predecessor.first);
            current->setValue(predecessor.second);
            return current;
        }
    }
    else if (current->getKey() > key) {
        current->setLeft(removeFromSubtree(current->getLeft(), key));
        return current;
    }
    else {
        current->setRight(removeFromSubtree(current->getRight(), key));
        return current;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {
    // base case
    if (current == nullptr){
        return;
    }
    deleteSubtree(current->getLeft());
    deleteSubtree(current->getRight());
    delete current;
    current = nullptr;
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current,
                                             List<pair<K, V>>* list) {
    if (current==nullptr){
        return;
    }
    list->insertLast({current->getKey(),current->getValue()});
    buildPreOrderTraversal(current->getLeft(),list);
    buildPreOrderTraversal(current->getRight(),list);
}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current,
                                            List<pair<K, V>>* list) {
    if (current==nullptr){
        return;
    }
    buildInOrderTraversal(current->getLeft(),list);
    list->insertLast({current->getKey(),current->getValue()});
    buildInOrderTraversal(current->getRight(),list);
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current,
                                              List<pair<K, V>>* list) {
  if (current==nullptr){
      return;
  }
  buildPostOrderTraversal(current->getLeft(),list);
  buildPostOrderTraversal(current->getRight(),list);
  list->insertLast({current->getKey(),current->getValue()});
}

template <typename K, typename V>
int LinkedBST<K, V>::countNodes(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) +
               this->countNodes(current->getRight()) + 1;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::verifyKeysBoundedBy(LinkedBSTNode<K, V>* current,
                                          bool minApplies, K minBound,
                                          bool maxApplies, K maxBound) {
    if (minApplies && current->getKey() < minBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a "
                            "right descendent with lesser key");
    }
    if (maxApplies && current->getKey() > maxBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a left "
                            "descendent with greater key");
    }
    if (current->getLeft() != nullptr) {
        verifyKeysBoundedBy(current->getLeft(), minApplies, minBound, true,
                            current->getKey());
    }
    if (current->getRight() != nullptr) {
        verifyKeysBoundedBy(current->getRight(), true, current->getKey(),
                            maxApplies, maxBound);
    }
}
