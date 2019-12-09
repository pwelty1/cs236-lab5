#ifndef DATALOGPROGRAM
#define DATALOGPROGRAM

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <exception>

#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram {

  private:
    vector<Rule> rules;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    set<string> domains;

  public:
    void addScheme(Predicate schme);
    void addFact(Predicate fct);
    void addRule(Rule rle);
    void addQuery(Predicate qry);
    void toString();
    vector<Rule> getRules() {return rules;}
    vector<Predicate> getSchemes() {return schemes;}
    vector<Predicate> getFacts() {return facts;}
    vector<Predicate> getQueries() {return queries;}

};

void DatalogProgram::addScheme(Predicate schme) {
  schemes.push_back(schme);
}

void DatalogProgram::addFact(Predicate fct) {
  facts.push_back(fct);
}

void DatalogProgram::addRule(Rule rle) {
  rules.push_back(rle);
}

void DatalogProgram::addQuery(Predicate qry) {
  queries.push_back(qry);
}

void DatalogProgram::toString(){
  cout << "Schemes(" << schemes.size() << "):" << endl;
  for (unsigned int i = 0; i < schemes.size();++i){
    cout << "  ";
    (schemes.at(i)).toString();
    cout << endl;
  }
  cout << "Facts(" << facts.size() << "):" << endl;
  for (unsigned int i = 0; i < facts.size();++i){
    cout << "  ";
    (facts.at(i)).toString();
    cout << "." << endl;
  }
  cout << "Rules(" << rules.size() << "):" << endl;
  for (unsigned int i = 0; i < rules.size();++i){
    cout << "  ";
    (rules.at(i)).toString();
  }
  cout << "Queries(" << queries.size() << "):" <<endl;
  for (unsigned int i = 0; i < queries.size();++i){
    cout << "  ";
    (queries.at(i)).toString();
    cout << "?" << endl;
  }

  for (unsigned int i=0; i<facts.size(); ++i){
    for (unsigned int j = 0; j < ((facts.at(i)).getParams()).size(); ++j) {
      domains.insert(((facts.at(i)).getParams()).at(j));
    }
  }
  set<string>::iterator it = domains.begin();
  cout << "Domain(" << domains.size() << "):" << endl;
  while (it != domains.end()){
	// Print the element
	   cout << "  "<< (*it) << endl;
	//Increment the iterator
  	 it++;
  }


  //
}

#endif
