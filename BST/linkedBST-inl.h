/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>
#include <vector>

#include "adts/list.h"
#include "adts/queue.h"
#include "adts/stlList.h"
#include "adts/stlQueue.h"

#include "linkedBSTNode.h"
#include "helpers.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinkedBST<K, V>::LinkedBST() {
    this->size = 0;
    this->root = nullptr;
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {
    deleteSubtree(this->root);
}

template <typename K, typename V> int LinkedBST<K, V>::getSize() {
    return this->size;
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {
    if (this->root != nullptr) {
        return false;
    }
    return true;
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {
    this->root = insertInSubtree(this->root, key, value);
}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {
    updateInSubtree(this->root, key, value);
}

template <typename K, typename V> V LinkedBST<K, V>::get(K key) {
    V value = findInSubtree(this->root, key);
    return value;
}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {
    return containsInSubtree(this->root, key);
}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {
    this->root = removeFromSubtree(this->root, key);
}

template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {
    vector<pair<K,V>> list = this->traverseLevelOrder();
    vector<K> keys;
    for (int i=0; i<list.size(); i++) {
        keys.push_back(list[i].first);
    }
    return keys;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::getItems() {
    return this->traverseLevelOrder();
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {
    return getHeightInSubtree(this->root);
}

template <typename K, typename V> K LinkedBST<K, V>::getMaxKey() {
    return getMaxInSubtree(this->root).first;
}

template <typename K, typename V> K LinkedBST<K, V>::getMinKey() {
    return getMinInSubtree(this->root).first;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {
  // Use the helper buildPreOrderTraversal
  // Also consider using dynamicListToStaticVector in helpers.h
   List<pair<K, V>>* list= new STLList<pair<K, V>>;
   buildPreOrderTraversal(this->root,list);
   vector<pair<K, V>> traversal = dynamicListToStaticVector(list);
   delete list;
   return traversal;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {
  // Use the helper buildInOrderTraversal
  // Also consider using dynamicListToStaticVector in helpers.h
    List<pair<K, V>>* list= new STLList<pair<K, V>>;
    buildInOrderTraversal(this->root,list);
    vector<pair<K, V>> traversal = dynamicListToStaticVector(list);
    delete list;
    return traversal;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {
  // Use the helper buildPostOrderTraversal
  // Also consider using dynamicListToStaticVector in helpers.h
  List<pair<K, V>>* list= new STLList<pair<K, V>>;
  buildPostOrderTraversal(this->root,list);
  vector<pair<K, V>> traversal = dynamicListToStaticVector(list);
  delete list;
  return traversal;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseLevelOrder() {
  // Do a breadth-first search (no need to mark visited or generate path)
  STLQueue<LinkedBSTNode<K,V>*> queue;
  vector<pair<K, V>> list;
  LinkedBSTNode<K,V>* current;
  queue.enqueue(this->root);
  while(!queue.isEmpty()) {
      current = queue.dequeue();
      list.push_back({current->getKey(), current->getValue()});
      if (current->getLeft()!=nullptr){
          queue.enqueue(current->getLeft());
      }
      if (current->getRight()!=nullptr){
          queue.enqueue(current->getRight());
      }
  }

  return list;
}

template <typename K, typename V> void LinkedBST<K, V>::checkInvariants() {
    if (this->countNodes(this->root) != this->size) {
        throw runtime_error(
            "Problem in BST: Node count doesn't match tree size");
    }
    if (this->root != nullptr) {
        // The bounds provided here are arbitrary because the false
        // arguments indicate that they do not apply.  But we need a
        // value of type K to fill this parameter since we don't have
        // globally min/max K values generically.
        this->verifyKeysBoundedBy(this->root, false, this->root->getKey(),
                                  false, this->root->getKey());
    }
}
