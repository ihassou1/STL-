#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

// This module contains a helper function to standardize error message
// generation in template classes.

#include <string>

namespace cs35 {
    template <typename T>
    std::string to_string(T t) {
        return std::to_string(t);
    }

    std::string to_string(std::string s);
}
