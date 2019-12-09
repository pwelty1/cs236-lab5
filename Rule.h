#ifndef RULE
#define RULE

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <exception>

#include "Predicate.h"

using namespace std;

class Rule {

private:
  Predicate headPred;
  vector<Predicate> predicates;

public:
  void addPredicate(Predicate predi);//,string tempid,vector<string> paramz);
  void toString();
  void setHeadPred(string tempid, vector<string> paramz);
  void clearPredicates();
  Predicate getHeadPred(){return headPred;}
  vector<Predicate> getPredicates() {return predicates;}
};

void Rule::toString() {
  headPred.toString();
  cout << " :- ";
  (predicates.at(0)).toString();
  for(unsigned int i = 1; i < predicates.size(); ++i) {
    cout <<",";
    (predicates.at(i)).toString();
  }
  cout << "." << endl;
}

void Rule::addPredicate(Predicate predi){//, string id, vector<string> paramz) {
  //predi.setId(id);
  //string tempParam;
  //for (int i = 0; i< paramz.size(); ++i){
    //tempParam = paramz.at(i);
    //predi.addParam(tempParam);
  //}
  predicates.push_back(predi);
}

void Rule::setHeadPred(string tempid, vector<string> paramz) {
  headPred.setId(tempid);
  string tempParam;
  for (unsigned int i = 0; i< paramz.size(); ++i){
    tempParam = paramz.at(i);
    headPred.addParam(tempParam);
  }
}

void Rule::clearPredicates() {
  predicates.clear();
}

#endif
