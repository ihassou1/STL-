/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>


#include "hashFunctions.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {
    this->hashTable = new LinearDictionary<K,V> [5];
    this->capacity = 5;
    this->maxLoadFactor = 0.75;
    this->size=0;
}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {
    this->hashTable = new LinearDictionary<K,V> [5];
    this->capacity = 5;
    this->maxLoadFactor = maxLoadFactor;
    this->size=0;
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {
    delete [] this->hashTable;

}

template <typename K, typename V> int HashTable<K, V>::getSize() {
    return this->size;
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {
   return this->size==0;
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {
      int hashvalue=hash(key,this->capacity);
      this->hashTable[hashvalue].insert(key,value);
      this->size++;
      float load=float(this->size) / this->capacity ;
      if (load > this->maxLoadFactor){
        expandCapacity();
      }
}

template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {
  int hashvalue=hash(key,this->capacity);
  this->hashTable[hashvalue].update(key,value);
}

template <typename K, typename V> V HashTable<K, V>::get(K key) {
    int hashvalue=hash(key,this->capacity);
    return this->hashTable[hashvalue].get(key);
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {
  int hashvalue=hash(key,this->capacity);
  return this->hashTable[hashvalue].contains(key);
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {
  int hashvalue=hash(key,this->capacity);
  return this->hashTable[hashvalue].remove(key);
  this->size--;
}

template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {
  vector<K> answer={};
  for (int i=0;i<this->capacity;i++){
    vector<K> dictionaryAtI=this->hashTable[i].getKeys();
    answer.insert(answer.end(),dictionaryAtI.begin(),dictionaryAtI.end());
  }
  return answer;
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {
  vector<pair<K,V>> answer={};
  for (int i=0;i<this->capacity;i++){
    vector<pair<K,V>> dictionaryAtI=this->hashTable[i].getItems();
    answer.insert(answer.end(),dictionaryAtI.begin(),dictionaryAtI.end());
  }
  return answer;
}

template <typename K, typename V> void HashTable<K, V>::expandCapacity() {
    int newCapacity=this->capacity * 2 ;
    LinearDictionary<K,V> * newArray = new LinearDictionary<K,V> [newCapacity];
    for (int i=0;i<this->capacity;i++){
      vector<pair<K,V>> dictionaryAtI=this->hashTable[i].getItems();
      for (int j=0;j<dictionaryAtI.size();j++){
        pair<K,V> item=dictionaryAtI[j];
        int hashIndex=hash(item.first,newCapacity);
        newArray[hashIndex].insert(item.first,item.second);
      }
    }
    delete [] this->hashTable;
    this->hashTable=newArray;
    this->capacity=newCapacity;
    newArray=NULL;
}

// TODO: put any other definitions here
