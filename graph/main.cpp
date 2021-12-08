/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/graph.h"
#include "adjacencyListGraph.h"
#include "graphAlgorithms.h"
#include <iostream>
#include "adjacencyListUndirectedGraph.h"
using namespace std;

int takeInput();
void doDFS(Graph<string, int, int>* graph);
void doBFS(Graph<string, int, int>* graph);
void doSSSP(Graph<string, int, int>* graph);

int main() {
  Graph<string,int,int>* graph =new AdjacencyListUndirectedGraph<string,int,int> ;
  graph->insertVertex("Mar");
  graph->insertVertex("LPAC");
  graph->insertVertex("Kohl");
  graph->insertVertex("Sing");
  graph->insertVertex("Par");
  graph->insertVertex("Trot");
  graph->insertVertex("Bear");
  graph->insertVertex("Sci");
  graph->insertEdge("Sci","Sing",0,3);
  graph->insertEdge("LPAC","Mar",0,3);
  graph->insertEdge("Kohl","LPAC",0,2);
  graph->insertEdge("Sing","Bear",0,2);
  graph->insertEdge("Par","Kohl",0,4);
  graph->insertEdge("Trot","Sing",0,5);
  graph->insertEdge("Bear","Kohl",0,2);
  graph->insertEdge("Sci","Bear",0,4);
  graph->insertEdge("Sci","Mar",0,6);
  graph->insertEdge("Kohl","Trot",0,3);
  int input = takeInput();
  while (input != 0){
    if (input >3 || input <0){
      cout << "Invalid input, enter 0,1,2,or 3" <<endl;
    }
    if (input ==1){
      doDFS(graph);
    }
    if (input == 2){
        doBFS(graph);
    }
    if (input == 3) {
        doSSSP(graph);
    }
    input = takeInput();
  }

 delete graph;
 return 0;

}

int takeInput(){
  int userInput;
  cout<< "                          " <<endl ;
  cout<< "Let's explore Swarthmore's north campus" <<endl ;
  cout<< "1. Reachability from one building to another" <<endl ;
  cout<< "2. Shortest length path from one building to another" <<endl ;
  cout<< "3. Distances from one building to all others" <<endl ;
  cout<< "0. Quit" <<endl ;
  cout<< "choice: " ;
  cin >> userInput ;
  return userInput;
}

void doDFS(Graph<string, int, int>* graph){
  string src;
  string dest;
  cout<< "Enter the first building: "  ;
  cin >> src ;
  cout<< "Enter the second building: "  ;
  cin >> dest ;
  if (reachableDFS(src,dest,graph)){
    cout << dest << " is reachable from " << src << endl;
  }
  else {
    cout << dest << " is not reachable from " << src << endl;
  }
}

void doBFS(Graph<string, int, int>* graph){
  string src;
  string dest;
  cout<< "Enter the first building: "  ;
  cin >> src ;
  cout<< "Enter the second building: "  ;
  cin >> dest ;
  vector<string> path = shortestLengthPathBFS(src, dest, graph);
  cout << "The shortest length path is: ";
  for (int i=0; i<path.size(); i++) {
      cout << path[i] << " ";
  }
  cout << endl;
}

void doSSSP(Graph<string, int, int>* graph){
  string src;
  string dest;
  cout<< "Enter the building to start from: "  ;
  cin >> src ;
  cout<< "Distance from " << src << " to all other buildings" << endl;
  Dictionary<string, int>* dictionary = singleSourceShortestPath(src, graph);
  vector<pair<string,int>> pathsDict = dictionary->getItems();
  for (int i=0; i<pathsDict.size(); i++) {
      cout << pathsDict[i].first << ": " << pathsDict[i].second << endl;
  }
  delete dictionary;
}
