/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "hashFunctions.h"
#include <string>

using std::string;

int hash(int value, int range) {
    // value is already an int, but could be out of range
    // use mod to put back into range
    int toReturn = value % range;
    if (toReturn < 0) {
        // NOTE: C++ % can return negative numbers if the value being
        // modded is negative.  To fix: add range to get positive.
        toReturn += range;
    }
    return toReturn;
}

int hash(string value, int range) {
    int hash_value = 0;
    for (int i = 0; i < value.length(); i++) {
        hash_value *= 31;       // prime number helps to avoid hash collisions
        hash_value += value[i]; // remember: characters can be treated as ints
    }

    // now, compress down to range
    int toReturn = hash_value % range;
    if (toReturn < 0) {
        toReturn += range;
    }
    return toReturn;
}
