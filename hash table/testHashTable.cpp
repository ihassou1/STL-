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
#include "hashFunctions.h"
#include "hashTable.h"

using namespace std;

SUITE(hashTable) {

    TEST(canCreateHashTable) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        delete dictionary;
    }

    TEST(hashTableTypesGeneric) {
        Dictionary<string, int>* dictionary = new HashTable<string, int>();
        delete dictionary;
    }

    TEST(hashTableSingleMapping) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        dictionary->insert(3, "three");
        CHECK_EQUAL("three", dictionary->get(3));
        delete dictionary;
    }

    TEST(hashTableManyMappings) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        for (int i = 0; i < 4; i++) {
            dictionary->insert(i, to_string(i));
        }
        for (int i = 0; i < 4; i++) {
            CHECK_EQUAL(to_string(i), dictionary->get(i));
        }
        delete dictionary;
    }

    TEST(hashTableCollision) {
        // Unless the table has a hefty, massive starting capacity, one of these
        // passes will trigger a collision.
        for (int inc = 1; inc <= 20; inc++) {
            Dictionary<int, string>* dictionary = new HashTable<int, string>();
            for (int i = 0; i < inc * 3; i += inc) {
                dictionary->insert(i, to_string(i));
            }
            for (int i = 0; i < inc * 3; i += inc) {
                CHECK_EQUAL(to_string(i), dictionary->get(i));
            }
            delete dictionary;
        }
    }

    TEST(doubleInsertFailure) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        dictionary->insert(0, "0");
        CHECK_THROW(dictionary->insert(0, "1"), std::exception);
        delete dictionary;
    }

    TEST(missingUpdateFailure) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        CHECK_THROW(dictionary->update(0, "1"), std::exception);
        delete dictionary;
    }

    TEST(hashTableUpdate) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        dictionary->insert(0, "0");
        dictionary->update(0, "1");
        CHECK_EQUAL("1", dictionary->get(0));
        dictionary->remove(0);
        CHECK_THROW(dictionary->get(0), std::exception);
        delete dictionary;
    }

    TEST(hashTableRemoveException) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        CHECK_THROW(dictionary->remove(0), std::exception);
        delete dictionary;
    }

    TEST(hashTableKeySet) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        for (int i = 0; i < 10; i++) {
            dictionary->insert(i, to_string(i));
        }
        vector<int> keys = dictionary->getKeys();
        for (int i = 0; i < 10; i++) {
            CHECK(std::find(keys.begin(), keys.end(), i) != keys.end());
        }
        delete dictionary;
    }

    TEST(hashTableLotsOfMappings) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        for (int i = 0; i < 100000; i++) {
            dictionary->insert(i, to_string(i));
        }
        for (int i = 0; i < 100000; i++) {
            CHECK_EQUAL(to_string(i), dictionary->get(i));
        }
        CHECK_EQUAL(100000, dictionary->getSize());
        delete dictionary;
    }

    TEST(hashTableLotsOfRandomMappings) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
        vector<int> values;
        default_random_engine generator;
        uniform_int_distribution<int> distribution(-2000000000, 2000000000);
        int i = 0;
        while (i < 100000) {
            int r = distribution(generator);
            if (!dictionary->contains(r)) {
                values.push_back(r);
                dictionary->insert(r, to_string(r));
                i++;
            }
        }
        for (i = 0; i < 100000; i++) {
            CHECK_EQUAL(to_string(values[i]), dictionary->get(values[i]));
        }
        CHECK_EQUAL(100000, dictionary->getSize());
        delete dictionary;
    }

    TEST(hashTableGetKeysAndGetItems) {
        Dictionary<int, string>* dictionary = new HashTable<int, string>();
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

    class BadHash {
      public:
        BadHash(int x) {
            this->x = x;
        }
        BadHash() {
            // do nothing
        }
        int x;
        bool operator==(BadHash& h) {
            return x == h.x;
        }
        bool operator<(const BadHash& h) const {
            return x < h.x;
        }
    };

    int hash(BadHash h, int range) {
        return 0;
    }

    TEST(hashTableWithBadHash) {
        Dictionary<BadHash, int>* dictionary = new HashTable<BadHash, int>();
        for (int i = 0; i < 1000; i++) {
            dictionary->insert(BadHash(i), i);
        }
        for (int i = 0; i < 1000; i++) {
            REQUIRE CHECK_EQUAL(i, dictionary->get(BadHash(i)));
        }
        dictionary->remove(0);
        for (int i = 1; i < 1000; i++) {
            REQUIRE CHECK_EQUAL(i, dictionary->get(BadHash(i)));
        }
        delete dictionary;
    }
}
