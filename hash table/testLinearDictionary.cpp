/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include <UnitTest++/UnitTest++.h>

#include "adts/dictionary.h"
#include "linearDictionary.h"

using namespace std;



SUITE(linearDictionary) {
    TEST(canCreateLinearDictionary) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        delete dictionary;
    }

    TEST(linearDictionaryTypesGeneric) {
        Dictionary<string, int>* dictionary =
            new LinearDictionary<string, int>();
        delete dictionary;
    }

    TEST(linearDictionarySingleMapping) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        dictionary->insert(3, "three");
        CHECK_EQUAL("three", dictionary->get(3));
        delete dictionary;
    }

    TEST(linearDictionaryManyMappings) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        for (int i = 0; i < 4; i++) {
            dictionary->insert(i, to_string(i));
        }
        for (int i = 0; i < 4; i++) {
            CHECK_EQUAL(to_string(i), dictionary->get(i));
        }
        delete dictionary;
    }

    TEST(linearDictionaryDoubleInsertFailure) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        dictionary->insert(0, "0");
        CHECK_THROW(dictionary->insert(0, "1"), std::exception);
        delete dictionary;
    }

    TEST(linearDictionaryMissingUpdateFailure) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        CHECK_THROW(dictionary->update(0, "1"), std::exception);
        delete dictionary;
    }

    TEST(linearDictionaryUpdate) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        dictionary->insert(0, "0");
        dictionary->update(0, "1");
        CHECK_EQUAL("1", dictionary->get(0));
        dictionary->remove(0);
        CHECK_THROW(dictionary->get(0), std::exception);
        delete dictionary;
    }

    TEST(linearDictionaryRemoveException) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        CHECK_THROW(dictionary->remove(0), std::exception);
        delete dictionary;
    }

    TEST(linearDictionaryKeySet) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        for (int i = 0; i < 10; i++) {
            dictionary->insert(i, to_string(i));
        }
        vector<int> keys = dictionary->getKeys();
        for (int i = 0; i < 10; i++) {
            CHECK(std::find(keys.begin(), keys.end(), i) != keys.end());
        }
        delete dictionary;
    }

    TEST(linearDictionaryMoreMappings) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        for (int i = 0; i < 1000; i++) {
            dictionary->insert(i, to_string(i));
        }
        for (int i = 0; i < 1000; i++) {
            CHECK_EQUAL(to_string(i), dictionary->get(i));
        }
        CHECK_EQUAL(1000, dictionary->getSize());
        delete dictionary;
    }

    TEST(linearDictionaryGetKeysAndGetItems) {
        Dictionary<int, string>* dictionary =
            new LinearDictionary<int, string>();
        vector<int> values, keys, itemKeys;
        default_random_engine generator;
        uniform_int_distribution<int> distribution(-2000000000, 2000000000);
        int i = 0;
        while (i < 1000) {
            int r = distribution(generator);
            if (!dictionary->contains(r)) {
                values.push_back(r);
                dictionary->insert(r, to_string(r));
                i++;
            }
        }

        keys = dictionary->getKeys();
        vector<pair<int, string>> items = dictionary->getItems();
        for (i = 0; i < 1000; i++) {
            itemKeys.push_back(items[i].first);
        }
        sort(values.begin(), values.end());
        sort(keys.begin(), keys.end());
        sort(itemKeys.begin(), itemKeys.end());
        if (keys.size() == 1000 && itemKeys.size() == 1000) {
            for (i = 0; i < 1000; i++) {
                CHECK_EQUAL(values[i], keys[i]);
                CHECK_EQUAL(values[i], itemKeys[i]);
            }
        } else {
            CHECK_EQUAL(keys.size(), 1000);
            CHECK_EQUAL(itemKeys.size(), 1000);
        }
        delete dictionary;
    }
}
