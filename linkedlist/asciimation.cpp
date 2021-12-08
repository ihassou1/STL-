/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;


int main(int argc, char** argv) {

    // if wrong number of arguments
    if (argc<2 || argc>3){
        throw runtime_error("usage: ./asciimation filename OR ./asciimation --reverse filename ");
    }

    // for 1 commandline argument
    else if (argc==2){
        string filename = argv[1];
        List<pair<int, string>>* movie = loadMovie(filename);
        playMovie(movie);

        delete movie; // de-allocate memory
    }

    // for 2 commandline arguments: first is reverse, second is filename
    else if (argc == 3) {
        string reverse = argv[1];

        // if first arg is wrong, throw error
        if (reverse != "--reverse") {
            throw runtime_error("usage for 2 arguments: ./asciimation --reverse filename");
        }

        // otherwise load movie, create reversed version, and play movie
        string filename = argv[2];
        List<pair<int, string>>* movie = loadMovie(filename);

        List<pair<int, string>>* reversedMovie = new LinkedList<pair<int, string>>;

        // remove last LLN from normal movie and add to reversedMovie
        int movieSize = movie->getSize();
        for (int i = 0; i < movieSize; i++) {
            reversedMovie->insertLast(movie->removeLast());
        }

        playMovie(reversedMovie);

        delete reversedMovie; // de-allocate memory
        delete movie;
    }
    return 0;
}
