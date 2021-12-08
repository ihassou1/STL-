#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <string>

using std::string;

// NOTE:
// This file declares a number of different functions all called "hash".  C++
// will determine which function you mean to call based upon the type of the
// argument you give; that is, if you call hash and pass it an int, you'll get
// the int version of hash.  This behavior is called "overloading".

/**
 * Generates a hash code for an integer.
 * @param value The integer to hash.
 * @param range The range of integers to hash to.
 * @return The hash of the provided integer.
 */
int hash(int value, int range);

/**
 * Generates a hash code for a string.
 * @param value The string to hash.
 * @param range The range of integers to hash to.
 * @return The hash of the provided string.
 */
int hash(string value, int range);

// NOTE:
// You could add as many hash functions as you wanted here.  If you wanted to
// be able to hash objects of some class, for instance, you could add such a
// hash function here.  You *must* have a hash function *somewhere* for each
// type of key your HashTable will have, though.
