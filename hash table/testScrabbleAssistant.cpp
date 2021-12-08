/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include <vector>

#include <UnitTest++/UnitTest++.h>

#include "adts/dictionary.h"
#include "hashFunctions.h"
#include "hashTable.h"
#include "scrabbleAssistant.h"

using namespace std;

/* helper check function that verifies there are no
   duplicate values in a vector */
template <typename T> void CHECK_VECTOR_NO_DUPLICATES(std::vector<T> expr);

/* helper check function that verifies that
   two vectors are set equivalent. An item
   is in the first vector iff it is in the
   second vector.  */
template <typename T>
void CHECK_VECTORS_SET_EQUAL(std::vector<T> first, std::vector<T> second);

SUITE(scrabbleAssistant) {
    ScrabbleAssistant* createSmallAssistant() {
        vector<string> words = {"seat", "teas", "eats", "sea", "tea", "set",
                                "sat",  "ate",  "eat",  "as",  "at"};
        ScrabbleAssistant* a = new ScrabbleAssistant(words);
        return a;
    }

    ScrabbleAssistant* createFullAssistant() {
        vector<string> words;
        ifstream dict("/usr/share/dict/words");
        string line;
        getline(dict, line);
        while (!dict.fail() && !dict.eof()) {
            words.push_back(line);
            getline(dict, line);
        }
        ScrabbleAssistant* a = new ScrabbleAssistant(words);
        return a;
    }

    TEST(spellCheck) {
        ScrabbleAssistant* a = createSmallAssistant();
        CHECK(a->spellCheck("teas"));
        CHECK(a->spellCheck("at"));
        CHECK(!a->spellCheck("tae"));
        CHECK(!a->spellCheck("saw"));
        CHECK(!a->spellCheck("seats"));
        delete a;
    }

    TEST(anagrams) {
        ScrabbleAssistant* a = createSmallAssistant();
        vector<string> answer = {"seat", "teas", "eats"};
        CHECK_VECTORS_SET_EQUAL(answer, a->anagramsOf("seat"));
        answer = {"tea", "ate", "eat"};
        CHECK_VECTORS_SET_EQUAL(answer, a->anagramsOf("aet"));
        CHECK_VECTORS_SET_EQUAL(answer, a->anagramsOf("tea"));
        answer = {"at"};
        CHECK_VECTORS_SET_EQUAL(answer, a->anagramsOf("at"));
        answer = {};
        CHECK_VECTORS_SET_EQUAL(answer, a->anagramsOf("a"));
        delete a;
    }

    TEST(wordfind) {
        ScrabbleAssistant* a = createSmallAssistant();
        vector<string> answer = {"seat", "teas", "eats", "sea", "tea", "set",
                                 "sat",  "ate",  "eat",  "as",  "at"};
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("seat"));
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("stae"));
        answer = {"tea", "ate", "eat", "at"};
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("aet"));
        answer = {"at"};
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("ta"));
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("at"));
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("taz"));
        answer = {"at", "as", "sat"};
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("szstat"));
        delete a;
    }

    TEST(bigwordfind) {
        ScrabbleAssistant* a = createFullAssistant();
        vector<string> answer = {"m", "moo", "moor", "o", "or", "r", "room"};
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("room"));
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("oomr"));
        answer = {
            "g",      "gilt",    "gin",      "glint", "glop",   "go",
            "got",    "i",       "in",       "ingot", "into",   "ion",
            "it",     "l",       "lingo",    "lint",  "lion",   "lip",
            "lit",    "lo",      "log",      "loin",  "long",   "lop",
            "loping", "lot",     "n",        "nil",   "nip",    "nit",
            "no",     "not",     "o",        "oil",   "oiling", "on",
            "opt",    "opting",  "p",        "pi",    "pig",    "piing",
            "piling", "pilot",   "piloting", "pin",   "ping",   "pint",
            "pinto",  "pit",     "piton",    "plot",  "poi",    "point",
            "pol",    "poling",  "pot",      "t",     "ti",     "tiling",
            "tin",    "ting",    "tip",      "tipi",  "to",     "tog",
            "toil",   "toiling", "ton",      "tong",  "top",    "login"
        };
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("piloting"));
        answer = {"l", "q", "x"};
        CHECK_VECTORS_SET_EQUAL(answer, a->findWords("qxl"));
        delete a;
    }
}

template <typename T> void CHECK_VECTOR_NO_DUPLICATES(std::vector<T> expr) {
    auto vec = expr;
    auto it = vec.begin();
    while (it < vec.end()) {
        if (std::find(it + 1, vec.end(), *it) != vec.end()) {
            CHECK_EQUAL(*it + " to be unique in vector",
                        *it + " in vector twice");
        }
        it++;
    }
}

template <typename T>
void CHECK_VECTORS_SET_EQUAL(std::vector<T> first, std::vector<T> second) {
    auto expected = first;
    auto actual = second;
    CHECK_VECTOR_NO_DUPLICATES(actual);
    CHECK_EQUAL(expected.size(), actual.size());
    for (int i = 0; i < expected.size(); i++) {
        if (std::find(actual.begin(), actual.end(), expected[i]) ==
            actual.end()) {
            CHECK_EQUAL(expected[i] + " to be in vector", "not");
        }
    }
    for (int i = 0; i < actual.size(); i++) {
        if (std::find(expected.begin(), expected.end(), actual[i]) ==
            expected.end()) {
            CHECK_EQUAL(actual[i] + " not to be in result",
                        actual[i] + "in result");
        }
    }
}
