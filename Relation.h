#ifndef RELATION
#define RELATION

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <exception>
#include <algorithm>
//#include <bool>

#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {

private:
  string name;
  Scheme attributes;
  set<Tuple> tuples;

public:
  string getName() {return name;}
  set<Tuple> getTuples() {return tuples;}
  Scheme getAttbs() {return attributes;}
  void addRelation(string nam, vector<string> attbs);
  void insert(vector<string> fcts);
  void toString();
  void selectConst(string cons, int index);
  void selectVar(vector<int> sameVars);
  void setTuples(set<Tuple> tpls);
  void clearAttributes() {return attributes.clear();}
  void project(map<string, int> sameVars, vector<int> order = {});
  void setAttributes(Scheme attbs);
  void rename(map<string, int> sameVars, bool preserve = false);
  void combineSchemes(Scheme rel2);
  bool isJoinable(Tuple rel1,Tuple rel2, vector<vector<int>> indices);
  void combineTuples(set<Tuple> rel1,set<Tuple> rel2,map<string,int> Rel1indices, map<string,int> Rel2indices);
  void unite(set<Tuple> newTuples);

};

void Relation::addRelation(string nam, vector<string> attbs) {
  name = nam;
  for(unsigned int i = 0; i < attbs.size(); ++i) {
    attributes.push_back(attbs.at(i));
  }
}

void Relation::insert(vector<string> fcts) {
  Tuple tple;
  //cout << fcts.size();
  for (unsigned int i = 0; i < fcts.size(); ++i) {
    tple.push_back(fcts.at(i));
  }
  tuples.insert(tple);
  tple.clear();
}

void Relation::toString() {
  set<Tuple>::iterator it = tuples.begin();
  while (it != tuples.end()){
	// Print the element
    for(unsigned int i = 0; i < attributes.size(); ++i){
      if (i == 0){
        cout << "  "<< attributes.at(i) << "=" << (*it).at(i);
        }
      else{
        cout << ", "<< attributes.at(i) << "=" << (*it).at(i);
        }
    }
    cout << endl;
	//Increment the iterator
  	it++;
  }
}

void Relation::selectConst(string cons, int index) {
  set<Tuple> selected;
  set<Tuple>::iterator it = tuples.begin();

  while (it != tuples.end()){
       if ((*it).at(index) == cons) {
         selected.insert(*it);
     }
     ++it;
  }
  setTuples(selected);
  selected.clear();
}

void Relation::selectVar(vector<int> sameVars) {
  set<Tuple> selected;
  set<Tuple>::iterator it = tuples.begin();
  vector<string> data;

  while (it != tuples.end()){
    for(unsigned int i = 0; i < sameVars.size(); ++i){
      data.push_back((*it).at(sameVars.at(i)));
      //cout << (*it).at(i) << endl;
    }
    bool same = true;
    for(unsigned int i = 0; i < data.size(); ++i){
      if (data.at(0) != data.at(i)){
        same = false;
      }
    }
    if (same == true){
      selected.insert(*it);
    }
    data.clear();
    ++it;
  }
  setTuples(selected);
  selected.clear();
}

void Relation::project(map<string, int> sameVars, vector<int> order) {
  set<Tuple> ts;
  Tuple t;
  vector<string> datas;

  if (order.size() > 0) {
    attributes.clear();
    for (unsigned int i = 0; i < order.size(); ++i){
      map<string, int>::iterator it;
      for (it = sameVars.begin(); it != sameVars.end(); it++ ){
        if (it->second == order.at(i)){
          attributes.push_back(it->first);
        }
      }
     }
    set<Tuple>::iterator it2 = tuples.begin();
    while (it2 != tuples.end()){
      for (unsigned int i = 0; i < order.size(); ++i){
        map<string, int>::iterator it1;
        for (it1 = sameVars.begin(); it1 != sameVars.end(); it1++ ){
          if (it1->second == order.at(i)){
            t.push_back((*it2).at((it1->second)));
          }
        }
       }
       ++it2;
       ts.insert(t);
       t.clear();
    }
    setTuples(ts);
    ts.clear();
  }
  else {
    set<Tuple>::iterator it2 = tuples.begin();
    while (it2 != tuples.end()){
      unsigned int k = 0;
      while (k < attributes.size()){
        map<string, int>::iterator it1;
        for (it1 = sameVars.begin(); it1 != sameVars.end(); it1++ ){
          unsigned int comp = it1->second;
        if (comp == k){
            t.push_back((*it2).at((it1->second)));
          }
        }
         ++k;
       }
       ++it2;
       ts.insert(t);
       t.clear();
    }
    setTuples(ts);
    ts.clear();
    //rename(sameVars);
  }
}

void Relation::rename(map<string, int> sameVars,bool preserve) {

  Scheme newAttbs;
  if (preserve == true) {
    for (unsigned int i = 0; i < attributes.size(); ++i){
      map<string, int>::iterator it1;
      for ( it1 = sameVars.begin(); it1 != sameVars.end(); it1++ ){
        unsigned int comp = it1->second;
        if (comp == i){
          attributes.at(i) = it1->first;
          }
        }
      }
    return;
  }

  for (unsigned int i = 0; i < attributes.size(); ++i){
    map<string, int>::iterator it1;
    for ( it1 = sameVars.begin(); it1 != sameVars.end(); it1++ ){
      unsigned int comp = it1->second;
      if (comp == i){
        newAttbs.push_back(it1->first);
      }

    }
  }
  setAttributes(newAttbs);
  newAttbs.clear();
}

void Relation::setTuples(set<Tuple> tpls) {
  set<Tuple>::iterator it = tpls.begin();
  tuples.clear();
  while (it != tpls.end()){

    tuples.insert(*it);
	//Increment the iterator
  	 it++;
  }
}

void Relation::setAttributes(Scheme attbs) {
  attributes.clear();
  for (unsigned int i = 0; i < attbs.size(); ++i) {
    attributes.push_back(attbs.at(i));
  }
}

void Relation::combineSchemes(Scheme rel2){
    for(unsigned int j = 0; j < rel2.size(); ++j) {
      attributes.push_back(rel2.at(j));
    }
}

bool Relation::isJoinable(Tuple rel1,Tuple rel2, vector<vector<int>> indices){
  for(unsigned int i= 0; i < indices.size(); ++i) {
      string rel1Contents = rel1.at((indices.at(i)).at(0));
      string rel2Contents = rel2.at((indices.at(i)).at(1));
      //cout << rel1Contents << " = " << rel2Contents << endl;
      if (rel1Contents!=rel2Contents){
        return false;
        }
      }
  return true;
    }


void Relation::combineTuples(set<Tuple> rel1,set<Tuple> rel2,map<string,int> Rel1indices, map<string,int> Rel2indices){
  set<Tuple> newTuples;
  vector<vector<int>> indices;
  vector<int> index;


  map<string, int>::iterator it1;
  for (it1 = Rel1indices.begin(); it1 != Rel1indices.end(); it1++ ){
      map<string, int>::iterator it2;
      for (it2 = Rel2indices.begin(); it2 != Rel2indices.end(); it2++ ){
        if(it1->first == it2->first){
          index.push_back(it1->second);
          index.push_back(it2->second);
          indices.push_back(index);
          index.clear();
        }
      }
  }

  Tuple t;
  set<Tuple>::iterator it3 = rel1.begin();
  while (it3 != rel1.end()){
    set<Tuple>::iterator it4 = rel2.begin();
    while (it4 != rel2.end()){
      if (isJoinable(*it3,*it4,indices)){
        for(unsigned int i = 0; i < (*it3).size(); ++i){
          t.push_back((*it3).at(i));
        }
        for(unsigned int i = 0; i < (*it4).size(); ++i){
          t.push_back((*it4).at(i));
        }
        newTuples.insert(t);
        t.clear();
      }
      it4++;
    }
	//Increment the iterator
  	it3++;
  }

  setTuples(newTuples);

}

void Relation::unite(set<Tuple> newTuples){
  set<Tuple>::iterator it1 = newTuples.begin();
  while (it1 != newTuples.end()){
    if(tuples.insert(*it1).second){
      tuples.insert(*it1);
      for(unsigned int i = 0; i < attributes.size(); ++i){
        if (i == 0){
          cout << "  "<< attributes.at(i) << "=" << (*it1).at(i);
          }
        else{
          cout << ", "<< attributes.at(i) << "=" << (*it1).at(i);
          }
      }
      cout << endl;
    }
    ++it1;
  }
}

#endif
