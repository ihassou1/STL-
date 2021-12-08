/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "scrabbleAssistant.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

ScrabbleAssistant::ScrabbleAssistant(vector<string> words) {
    this->anagrams = new HashTable<string,vector<string>>;
    for (int i=0; i<words.size(); i++) {
        string sortedWord = words[i];
        sort(sortedWord.begin(), sortedWord.end());
        if (this->anagrams->contains(sortedWord)) {
            vector<string> newAnagramsList = this->anagrams->get(sortedWord);
            newAnagramsList.push_back(words[i]);
            this->anagrams->update(sortedWord, newAnagramsList);
        }
        else {
            vector<string> newEntry = {words[i]};
            this->anagrams->insert(sortedWord, newEntry);
        }
    }
}

ScrabbleAssistant::~ScrabbleAssistant() {
    delete this->anagrams;
}

bool ScrabbleAssistant::spellCheck(string word) {
    string sorted=word;
    sort(sorted.begin(),sorted.end());
    if (!this->anagrams->contains(sorted)){
        return false;
    }
    vector<string> anagrams= this->anagrams->get(sorted);
    for (int i=0;i<anagrams.size();i++){
        if (anagrams[i]==word){
            return true;
        }
    }
    return false;
}

vector<string> ScrabbleAssistant::anagramsOf(string letters) {
    sort(letters.begin(), letters.end());
    if (this->anagrams->contains(letters)) {
        return this->anagrams->get(letters);
    }
    return {};
}

vector<string> ScrabbleAssistant::findWords(string letters) {
    vector<string> powerSet = stringPowerSet(letters);
    vector<string> powerSetAnagrams;
    for (int i=0; i<powerSet.size(); i++) {
        vector<string> anagramsI;
        sort(powerSet[i].begin(), powerSet[i].end());
        anagramsI = anagramsOf(powerSet[i]);
        powerSetAnagrams.insert(powerSetAnagrams.end(), anagramsI.begin(), anagramsI.end());
    }
    HashTable<string,int> uniqueAnagrams;
    for (int i=0; i<powerSetAnagrams.size(); i++) {
        if (!uniqueAnagrams.contains(powerSetAnagrams[i])) {
            uniqueAnagrams.insert(powerSetAnagrams[i], 0);
        }
    }
    return uniqueAnagrams.getKeys();
}

vector<string> ScrabbleAssistant::stringPowerSet(string letters){
  vector<string> result;
  //base case: return empty set if letters is empty
  if(letters == ""){
    result.push_back("");
    return result;
  }

  char firstChar = letters[0];
  string sub = letters.substr(1);

  //recursive case: find subset of last n-1 elements in set
  vector<string> smallerResult = stringPowerSet(sub);

  for(int i = 0; i < smallerResult.size(); i++){
      result.push_back(smallerResult[i]); // recursive results
      result.push_back(firstChar+smallerResult[i]); // append first element
  }
  return result;
}
// TODO: implement here any other methods that you choose to declare
