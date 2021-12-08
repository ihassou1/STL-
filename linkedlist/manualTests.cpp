/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <utility>


#include <iostream>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

LinkedList<int>* createListBackward(int size) {
    LinkedList<int>* list = new LinkedList<int>();
    for (int i = size - 1; i >= 0; i--) {
        list->insertFirst(i * 2);
    }
    list->checkInvariants();
    return list;
}

int main() {

    List<pair<int, string>>* list = loadMovie("test_data/scene1.asciimation");
    int i = 0;
    while (i < list->getSize()) {
        cout << list->get(i).first;
        i++;
    }
   playMovie(list);
   delete list;
    return 0;
}
