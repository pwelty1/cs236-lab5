#ifndef GRAPH
#define GRAPH
//CAN BE EMPY!!!!!
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <exception>
#include <stack>

#include "Node.h"

using namespace std;

class Graph {


  private:
    map<int, Node> nodes;
    stack<int> postOrder;
    vector<set<int>> SCCs;
    set<int> scc;

  public:
    void addNode(int id, Node nde);
    void toString();
    map<int, Node> getNodes() {return nodes;}
    void setNodes(map<int, Node> nds) { nodes = nds;}
    void dfsForest(stack<int> pOrder = {});
    void dfs(int id);
    void printPostOrder();
    void printSCC();
    stack<int> getPostOrder() {return postOrder;}
    void dfsSCC(int id);
    void resetVisits();
    vector<set<int>> getSCCs() {return SCCs;}
};

void Graph::addNode(int id, Node nde) {
  nodes.insert(pair<int, Node>(id, nde));
}

void Graph::toString(){
  map<int, Node>::iterator it1;
  for (it1 = nodes.begin(); it1 != nodes.end(); it1++){
    cout << "R" << it1->first << ":";
    set<int>::iterator it2 = ((it1->second).dependencies).begin();
    while (it2 != ((it1->second).dependencies).end()){
  	// Print the element
      if (it2 == ((it1->second).dependencies).begin()){
        cout << "R" << *it2;
      }
      else{
        cout << ",R" << *it2;
      }
  	//Increment the iterator
    	it2++;
    }
    cout << endl;
  }
}

void Graph::dfsForest(stack<int> pOrder) {
  if (pOrder.size() == 0){
    map<int, Node>::iterator it1;
    for (it1 = nodes.begin(); it1 != nodes.end(); it1++){
      if((it1->second).visited == false) {
        dfs(it1->first);
        postOrder.push(it1->first);
      }
    }
  }
  else {
    //cout << "done1";
    int stackSize = pOrder.size();
    for(unsigned int i = 0; i < stackSize; ++i){
      if(nodes[pOrder.top()].visited == false) {
        //cout << pOrder.top() << endl;
        scc.insert(pOrder.top());
        dfsSCC(pOrder.top());
        pOrder.pop();
        SCCs.push_back(scc);
        scc.clear();
      }
      else{
        //cout << pOrder.top() << endl;
        pOrder.pop();
      }
    }
  }
}

void Graph::dfsSCC(int id){
  nodes[id].visited = true;
  //cout << nodes[id].visited << endl;
  set<int> deps = nodes[id].dependencies;
  set<int>::iterator it2 = deps.begin();
  while (it2 != deps.end()){
    if(nodes[*it2].visited == false){
      //cout << *it2 << endl;
      scc.insert(*it2);
      dfsSCC(*it2);
    }
    ++it2;
  }
}

void Graph::dfs(int id){
  nodes[id].visited = true;
  //cout << nodes[id].visited << endl;
  set<int> deps = nodes[id].dependencies;
  set<int>::iterator it2 = deps.begin();
  while (it2 != deps.end()){
    if(nodes[*it2].visited == false){
      dfs(*it2);
      postOrder.push(*it2);
    }
    ++it2;
  }
}

void Graph::printPostOrder() {
  int si = postOrder.size();
  for(unsigned int i = 0; i < si; ++i){
    cout << postOrder.top();
    postOrder.pop();
  }
}

void Graph::printSCC(){
  cout << "[";
  for(unsigned int i = 0; i < SCCs.size(); ++i){
    cout << "[";
    set<int>::iterator it2 = (SCCs.at(i)).begin();
    while (it2 != (SCCs.at(i)).end()){
      cout << *it2;
      ++it2;
    }
    cout << "]";
  }
  cout << "]" << endl;;
}

void Graph::resetVisits() {
  map<int, Node>::iterator it1;
  for (it1 = nodes.begin(); it1 != nodes.end(); it1++){
    (it1->second).visited = false;
  }
}

#endif
