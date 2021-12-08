/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    STLStack<V> stack;
    STLHashTable<V,bool> visited;
    stack.push(src);
    visited.insert(src,true);
    while (!stack.isEmpty()){
      V current =stack.pop();
      if (current==dest){
        return true;
      }
      vector<V> neighbors=g->getNeighbors(current);
      for (int i=0;i<neighbors.size();i++){
        if (!visited.contains(neighbors[i])){
          stack.push(neighbors[i]);
          visited.insert(neighbors[i],true);
        }
      }
    }
    return false;
}

template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
    vector<V> path;
    STLQueue<V> queue;
    STLHashTable<V,V> previous;
    queue.enqueue(src);
    previous.insert(src, src);
    while (!queue.isEmpty()) {
        V current = queue.dequeue();
        if (current == dest) {
            V temp = dest;
            while (temp != src) {
                path.insert(path.begin(), temp);
                temp = previous.get(temp);
            }
            path.insert(path.begin(), src);
            return path;
        }
        else {
            vector<V> neighbors = g->getNeighbors(current);
            for (int i=0; i<neighbors.size(); i++) {
                if (!previous.contains(neighbors[i])) {
                    previous.insert(neighbors[i], current);
                    queue.enqueue(neighbors[i]);
                }
            }
        }
    }
    return path;
}

template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {
    Dictionary<V, W>* cost = new STLHashTable<V,W>;
    STLMinPriorityQueue<W,V> pq;
    cost->insert(src,0);
    pq.insert(0,src);
    while (!pq.isEmpty()) {
        W currPriority = pq.peekPriority();
        V currVertex = pq.remove();
        W currCost = cost->get(currVertex);
        if (currCost == currPriority) {
            vector<V> neighbors = g->getNeighbors(currVertex);
            for (int i=0; i<neighbors.size(); i++) {
                V next = neighbors[i];
                Edge<V,E,W> edge = g->getEdge(currVertex, neighbors[i]);
                W newCost = currCost + edge.getWeight();
                if (!cost->contains(next)) {
                    cost->insert(next, newCost);
                    pq.insert(newCost, next);
                }
                else if (newCost < cost->get(next)) {
                    cost->update(next, newCost);
                    pq.insert(newCost, next);
                }
            }
        }
    }
    return cost;
}
