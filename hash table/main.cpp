/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "scrabbleAssistant.h"
#include "adts/stlMaxPriorityQueue.h"

using namespace std;

ScrabbleAssistant* createAssistant(string dictionaryFilename);
bool mainMenu(ScrabbleAssistant* assistant);

int main(int argc, char** argv) {
    string filename;

    // first, handle possible command line arguments
    if (argc == 1) {
        // use default dictionary
        filename = "/usr/share/dict/words";
    } else if (argc == 2) {
        // use user-specified dictionary
        filename = argv[1];
    } else {
        cout << "Invalid number of arguments." << endl;
        return 1;
    }

    // instantiate new scrabble assistant
    ScrabbleAssistant* assistant = createAssistant(filename);

    // main program loop
    bool quit = false;
    while (!quit) {
        quit = mainMenu(assistant);
    }

    delete assistant;
    return 0;
}

ScrabbleAssistant* createAssistant(string dictionaryFilename) {
    ifstream dictionaryFile(dictionaryFilename.c_str());
    vector<string> words;
    string word;
    dictionaryFile >> word;
    while (!dictionaryFile.fail()) {
        words.push_back(word);
        dictionaryFile >> word;
    }
    ScrabbleAssistant* assistant = new ScrabbleAssistant(words);
    return assistant;
}

bool mainMenu(ScrabbleAssistant* assistant) {
    cout << "Menu:" << endl;
    cout << "  1) Spellcheck a word" << endl;
    cout << "  2) Get anagrams of a word" << endl;
    cout << "  3) Get valid words from tiles" << endl;
    cout << "  0) Exit" << endl;

    int choice;
    string word, tiles;
    cout << "Enter your choice (0-3): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Which word would you like to spellcheck? ";
        cin >> word;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        cout << "\"" << word << "\" is ";
        if (!assistant->spellCheck(word)) {
            cout << "not ";
        }
        cout << "a valid word." << endl;

    } else if (choice == 2) {
        cout << "Which word would you like to use? " ;
        cin >> word;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        vector<string> anagrams = assistant->anagramsOf(word);
        if (anagrams.size() == 0) {
            cout << "There are no anagrams of that \"word\"." << endl;
        } else {
            cout << "The anagrams of \"" << word << "\" are:" << endl;
            for (int i = 0; i < anagrams.size(); i++) {
                cout << "    " << anagrams[i] << endl;
            }
        }
    } else if (choice == 3) {
        cout << "What letters do you have available? ";
        cin >> tiles;
        transform(tiles.begin(), tiles.end(), tiles.begin(), ::tolower);
        vector<string> words = assistant->findWords(tiles);
        if (words.size() == 0) {
            cout << "There are no words that can be made with those letters."
                 << endl;
        } else {
            STLMaxPriorityQueue<int,string> pq;
            for (int i = 0; i < words.size(); i++) {
              pq.insert(words[i].size(),words[i]);
            }
            cout << "You can make the following words:" << endl;
            for (int i = 0; i < words.size(); i++) {
                cout << "    " << pq.remove() << endl;
            }
        }

    } else if (choice == 0) {
        cout << "Goodbye!" << endl;
        return true;

    } else {
        cout << "I didn't understand that instruction." << endl;
    }
    cout << endl;
    return false;
}
