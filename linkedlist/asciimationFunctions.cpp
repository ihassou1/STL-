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

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

List<pair<int, string>>* loadMovie(string filename) {
    ifstream myFile;
    string data;

    myFile.open(filename);
    if(!myFile.is_open()) {
      throw runtime_error("file " + filename + "failed to open ");
    }

    // create linked list of pairs
    LinkedList<pair<int,string>> *frameList = new LinkedList<pair<int,string>>;

    // store first frame count
    getline(myFile, data);
    int frameCount = stoi(data);

    while (!myFile.eof()) {
        string thirteenLines = "";

        // read the next 13 lines which form a frame
        for (int i = 0; i < 13; i++) {
            getline(myFile, data);
            thirteenLines += data + "\n";
        }

        // store the frame and add to linked list
        pair<int,string> frame(frameCount, thirteenLines);
        frameList->insertLast(frame);

        // store duration of frame
        getline(myFile, data);
        if (data != "") {
            frameCount = stoi(data);
        }
    }
    myFile.close();
    return frameList;

}

void playMovie(List<pair<int, string>>* list) {
    for (int i=0; i<list->getSize();i++){
        cout << list->get(i).second << endl;
        usleep((1000000/15) * list->get(i).first);
        system("clear");
    }

}
