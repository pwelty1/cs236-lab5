#include <iostream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <locale>
#include <map>

#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Graph.h"


using namespace std;

int main (){
  vector<Rule> rules;
  Rule rule;
  Predicate predicate;
  vector<Predicate> Predis;
  vector<string> parameters;

  predicate.setId("Alpha");
  predicate.addParam("\'x\'");
  predicate.addParam("\'y\'");
  predicate.addParam("\'z\'");

  rule.setHeadPredi(predicate);
  predicate.clearParams();

  predicate.setId("Bravo");
  predicate.addParam("\'a\'");
  predicate.addParam("\'b\'");
  predicate.addParam("\'z\'");

  rule.addPredicate(predicate);
  predicate.clearParams();

  predicate.setId("Charlie");
  predicate.addParam("\'x\'");
  predicate.addParam("\'y\'");
  predicate.addParam("\'c\'");

  rule.addPredicate(predicate);
  predicate.clearParams();

  rules.push_back(rule);
  rule.clearPredicates();

  predicate.setId("Bravo");
  predicate.addParam("\'x\'");
  predicate.addParam("\'y\'");
  predicate.addParam("\'z\'");

  rule.setHeadPredi(predicate);
  predicate.clearParams();

  predicate.setId("Charlie");
  predicate.addParam("\'a\'");
  predicate.addParam("\'x\'");
  predicate.addParam("\'z\'");

  rule.addPredicate(predicate);
  predicate.clearParams();

  predicate.setId("Alpha");
  predicate.addParam("\'y\'");
  predicate.addParam("\'a\'");
  predicate.addParam("\'b\'");

  rule.addPredicate(predicate);
  predicate.clearParams();

  rules.push_back(rule);
  rule.clearPredicates();

  predicate.setId("Charlie");
  predicate.addParam("\'x\'");
  predicate.addParam("\'y\'");
  predicate.addParam("\'z\'");

  rule.setHeadPredi(predicate);
  predicate.clearParams();

  predicate.setId("Delta");
  predicate.addParam("\'z\'");
  predicate.addParam("\'y\'");
  predicate.addParam("\'x\'");

  rule.addPredicate(predicate);
  predicate.clearParams();

  rules.push_back(rule);
  rule.clearPredicates();

  predicate.setId("Delta");
  predicate.addParam("\'x\'");
  predicate.addParam("\'y\'");
  predicate.addParam("\'z\'");

  rule.setHeadPredi(predicate);
  predicate.clearParams();

  predicate.setId("Charlie");
  predicate.addParam("\'z\'");
  predicate.addParam("\'x\'");
  predicate.addParam("\'y\'");

  rule.addPredicate(predicate);
  predicate.clearParams();

  rules.push_back(rule);
  rule.clearPredicates();

  predicate.setId("Delta");
  predicate.addParam("\'x\'");
  predicate.addParam("\'y\'");
  predicate.addParam("\'z\'");

  rule.setHeadPredi(predicate);
  predicate.clearParams();

  predicate.setId("Echo");
  predicate.addParam("\'y\'");
  predicate.addParam("\'z\'");
  predicate.addParam("\'x\'");

  rule.addPredicate(predicate);
  predicate.clearParams();

  rules.push_back(rule);
  rule.clearPredicates();

  int id = 0;
  set<int> deps;
  Node newNode;
  Graph forwardGraph;

  //creating the depedency graph
  for(unsigned int i = 0; i < rules.size(); ++i){
    id = i;
    vector<Predicate> preds = (rules.at(i)).getPredicates();
    for (unsigned int j = 0; j < preds.size(); ++j) {
      string name = (preds.at(j)).getId();
      for (unsigned int k = 0; k < rules.size(); ++k) {
        if (name == ((rules.at(k)).getHeadPred()).getId()) {
          deps.insert(k);
        }
      }
    }
    newNode.dependencies = deps;
    forwardGraph.addNode(id, newNode);
    deps.clear();
  }

  cout << "Dependency Graph" << endl;
  forwardGraph.toString();
  cout << endl;

  Graph reverseGraph;
  map<int, Node> nuds = forwardGraph.getNodes();


  map<int, Node>::iterator it1;
  (newNode.dependencies).clear();
  for (it1 = nuds.begin(); it1 != nuds.end(); it1++){
    reverseGraph.addNode(it1->first, newNode);
  }
  //reverseGraph.toString();

  map<int, Node> nodez = reverseGraph.getNodes();;
  map<int, Node>::iterator it2;
  (newNode.dependencies).clear();
  for (it2 = nuds.begin(); it2 != nuds.end(); it2++){
    set<int>::iterator it3 = ((it2->second).dependencies).begin();
    while (it3 != ((it2->second).dependencies).end()){
      (nodez[*it3].dependencies).insert(it2->first);
  	// Print the element
  	//Increment the iterator
    	it3++;
    }
  }
  reverseGraph.setNodes(nodez);

  cout << "Reverse Graph" << endl;
  reverseGraph.toString();
  cout << endl;

  reverseGraph.dfsForest();

  cout << "Reverse Graph DFS Post Order : Note, this Post Order is coming of a Stack" << endl;
  stack<int> pOrder = reverseGraph.getPostOrder();
  int si = pOrder.size();
  cout << "[";
  for(unsigned int i = 0; i < si; ++i){
    cout << pOrder.top();
    pOrder.pop();
  }
  cout << "]" << endl << endl;

  forwardGraph.resetVisits();
  forwardGraph.dfsForest(reverseGraph.getPostOrder());
  cout << "Strongly Connected Components" << endl;
  //forwardGraph.printSCC();
  vector<set<int>> sccs = forwardGraph.getSCCs();
  for(unsigned int i = 0; i < sccs.size(); ++i) {
    set<int>::iterator it2 = (sccs.at(i)).begin();
    cout << "SCC"<< i+1 << ": ";
    while (it2 != (sccs.at(i)).end()){
      if (it2 == (sccs.at(i)).begin()){
        cout << "R" << *it2;
      }
      else {
        cout << ",R"<< *it2;
      }
      ++it2;
    }
    cout << endl;
  }
  cout << endl;
  return 0;
}
