#ifndef NODE
#define NODE
//CAN BE EMPY!!!!!
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <exception>

using namespace std;

class Node {

  public:
    set<int> dependencies;
    bool visited = false;

};

#endif
