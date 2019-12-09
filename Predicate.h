#ifndef PREDICATE
#define PREDICATE

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <exception>
#include <list>
#include <iterator>
//#include <bool>

using namespace std;

class Predicate {

private:
  string id;
  vector<string> parameters;
  string parameter;

public:
  void setId(string newId);
  void addParam(string param);
  void toString();
  void clearParams();
  string getId(){return id;}
  vector<string> getParams() {return parameters;}

};

void Predicate::addParam(string param) {

  parameters.push_back(param);
}

void Predicate::setId(string newId){
  id = newId;
}

void Predicate::toString() {
  cout << id << "(" << parameters.at(0);
  for (unsigned int i = 1; i< parameters.size(); ++i){
    cout << "," << parameters.at(i);
  }
  cout << ")";

}

void Predicate::clearParams(){
  parameters.clear();
}



#endif
