/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {
}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {
    return this->dictionary.size();
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {
    return this->dictionary.size() == 0;
}

template <typename K, typename V>
void LinearDictionary<K, V>::insert(K key, V value) {
    for (int i=0; i<this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            throw runtime_error("key already in dictionary");
        }
    }
    this->dictionary.push_back({key, value});
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {
    for (int i=0; i<this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            this->dictionary[i].second = value;
            return;
        }
    }
    throw runtime_error("key not found");
}

template <typename K, typename V> V LinearDictionary<K, V>::get(K key) {
    for (int i=0; i<this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            return this->dictionary[i].second;
        }
    }
    throw runtime_error("key not found");
}

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {
    for (int i=0; i<this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            return true;
        }
    }
    return false;
}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {
    for (int i=0; i<this->dictionary.size(); i++) {
        if (this->dictionary[i].first == key) {
            removeFromVector(this->dictionary, i);
            return;
        }
    }
    throw runtime_error("key not found");
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {
    vector<K> keys;
    for (int i=0; i<this->dictionary.size(); i++) {
        keys.push_back(this->dictionary[i].first);
    }
    return keys;
}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {
    return this->dictionary;
}

template <typename T> void removeFromVector(vector<T> &list, int index){
  if(index < 0 || index >= list.size()){
    throw runtime_error("index out of range in removeFromVector");
  }
  list.erase(list.begin()+index, list.begin()+index+1);
}

// TODO: put any other definitions here
