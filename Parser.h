#ifndef PARSER
#define PARSER

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <exception>

//#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"

using namespace std;

class Parser {

  private:
    int index = 0;
    vector<Token> tokens;
    string temp="";
    string tempId = "";
    string tempParam = "";
    Predicate predz;
    vector<string> params;
    vector<Predicate> predis;
    DatalogProgram newData;

  public:
    Parser(vector<Token> tkns);
    void parse();
    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();
    void parseExpression();
    void parseOperator();
    void match(Token current, string correct);
    DatalogProgram getDataprogram(){return newData;}

};
//#include "Parser.h"
//#include "Token.h"
Parser::Parser(vector<Token> tkns){
    for(unsigned int i = 0; i < tkns.size(); i++) {
      tokens.push_back(tkns.at(i));
      //(tokens.at(i)).toString();
    }
    return;
}

void Parser::match(Token current,string correct) {
  //cout << "failed?0" << endl;
  while ((tokens.at(index)).gettypeOut() == "COMMENT"){
    ++index;
  }
  //cout << "failed?1" << endl;
  if ((tokens.at(index)).gettypeOut() == correct) {
    temp += (tokens.at(index)).getValue();
    //cout << index << " " << (tokens.at(index)).gettypeOut()<< endl;
    ++index;
  }
  else{
    //current.toString();
    throw tokens.at(index);
  }
  int i = (tokens.size())-1;
  //cout<< "failed?" << endl;
  //cout<< index << endl;
  if (index >= i){return;}
  (tokens.at(index)).gettypeOut();
  if (index < i) {
    while ((tokens.at(index)).gettypeOut() == "COMMENT"){
      //(tokens.at(index)).toString();
      ++index;
      ++i;
    }
  }

}

void Parser::parse() {
  //cout<< "________PARSING________"<< endl;
  try {
    parseDatalogProgram();
    //cout << "Success!" << endl;
    //newData.toString();

  }
  catch(Token e){
    cout <<"Failure!"<< endl;
    cout << "  ";
    e.toString();
  }
}

void Parser::parseDatalogProgram() {
  //datalogProgram	->	SCHEMES COLON scheme schemeList
	//	        FACTS COLON factList
	//	        RULES COLON ruleList
	//	        QUERIES COLON query queryList


  match(tokens.at(index),"SCHEMES");
  match(tokens.at(index),"COLON");

  parseScheme();

  parseSchemeList();

  match(tokens.at(index),"FACTS");

  match(tokens.at(index),"COLON");

  parseFactList();

  match(tokens.at(index),"RULES");

  match(tokens.at(index),"COLON");

  parseRuleList();

  match(tokens.at(index),"QUERIES");

  match(tokens.at(index),"COLON");

  parseQuery();
  //cout << "completed0" << endl;

  parseQueryList();
  //cout << "completed1" << endl;

  match(tokens.at(index),"EOF");
  //cout << "completed2" << endl;
}

void Parser::parseSchemeList(){
  //schemeList	->	scheme schemeList | lambda
    if((tokens.at(index)).gettypeOut() == "ID"){
      parseScheme();
      parseSchemeList();
    }
    else if((tokens.at(index)).gettypeOut() == "FACTS"){
      return;
    }
}

void Parser::parseFactList() {
  //factList	->	fact factList | lambda
  if((tokens.at(index)).gettypeOut() == "ID"){
    parseFact();
    parseFactList();
  }
  else if ((tokens.at(index)).gettypeOut() == "RULES"){
    return;
  }
}

void Parser::parseRuleList() {
  //ruleList	->	rule ruleList | lambda
  if((tokens.at(index)).gettypeOut() == "ID"){
    parseRule();
    parseRuleList();
  }
  else if ((tokens.at(index)).gettypeOut() == "QUERIES"){
    return;
  }
}

void Parser::parseQueryList(){
  //queryList	->	query queryList | lambda
  if ((tokens.at(index)).gettypeOut() == "EOF"){
    //cout<< "did not fail2" << endl;
    return;
  }
  else if((tokens.at(index)).gettypeOut() == "ID"){
    parseQuery();
    parseQueryList();
  }
}

void Parser::parseScheme(){
  Predicate scheme;

  temp = "";
  match(tokens.at(index), "ID");
  tempId = temp;

  match(tokens.at(index), "LEFT_PAREN");

  temp = "";
  match(tokens.at(index), "ID");
  tempParam = temp;
  scheme.addParam(tempParam);

  parseIdList();

  for (unsigned int i = 0; i< params.size(); ++i){
    tempParam = params.at(i);
    scheme.addParam(tempParam);
  }
  params.clear();

  match(tokens.at(index), "RIGHT_PAREN");
  scheme.setId(tempId);
  newData.addScheme(scheme);
  //if ((tokens.at(index)).gettypeOut() == "ID") {
    //return;
  //}
  //else if ((tokens.at(index)).gettypeOut() == "FACTS") {
    //return;
  //}
}

void Parser::parseFact(){
    Predicate fact;
  //fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD

  // declare a set of strings
  // std::set<string> domainSet;
  // add every string to the domainSet
    // will auto sort them
    // will throw out repeats
  // call to print set after the queries section has printed
    //std::set<std::string>::iterator it = setOfStr.begin();

    temp = "";
    match(tokens.at(index), "ID");
    tempId = temp;
    match(tokens.at(index), "LEFT_PAREN");
    temp = "";
    match(tokens.at(index), "STRING");
    // add string to domainSet
    tempParam = temp;
    fact.addParam(tempParam);
    parseStringList();
    // go into parseStringList and add every time it recurses

    for (unsigned int i = 0; i< params.size(); ++i){
      tempParam = params.at(i);
      fact.addParam(tempParam);
    }
    params.clear();

    match(tokens.at(index), "RIGHT_PAREN");
    match(tokens.at(index), "PERIOD");
    fact.setId(tempId);
    newData.addFact(fact);
}

void Parser::parseRule() {
  Rule rule;
  Predicate predi;
  //rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
  parseHeadPredicate();
  rule.setHeadPred(tempId,params);
  tempId = "";
  params.clear();
  match(tokens.at(index), "COLON_DASH");
  parsePredicate();
  rule.addPredicate(predz);
  predz.clearParams();
  params.clear();
  parsePredicateList();
  for (unsigned int i = 0; i < predis.size(); ++i){
    //predz.setId((predis.at(i)).getId());
    //predz.setParams((predis.at(i)).getParams());
    rule.addPredicate(predis.at(i));
    //predz.clearParams();
  }
  predis.clear();
  match(tokens.at(index), "PERIOD");

  newData.addRule(rule);
}

void Parser::parseQuery() {
  Predicate query;
  //cout << "completed4" << endl;//query	        ->      predicate Q_MARK
  parsePredicate();
  //cout << "completed5" << endl;
  newData.addQuery(predz);
  //.cout<<"here 0 "<< index << endl;
  predz.clearParams();
  match(tokens.at(index), "Q_MARK");
  //cout << "completed3" << endl;
  int i = tokens.size();
  if (index != i){
    if((tokens.at(index)).gettypeOut() == "EOF"){
      //cout << "did not fail1" << endl;
      return;
    }
  }

}

void Parser::parseHeadPredicate(){
  //headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
  temp = "";
  match(tokens.at(index), "ID");
  tempId = temp;
  match(tokens.at(index), "LEFT_PAREN");
  temp = "";
  match(tokens.at(index), "ID");
  tempParam = temp;
  params.push_back(tempParam);
  parseIdList();
  match(tokens.at(index), "RIGHT_PAREN");
}

void Parser::parsePredicate(){
  //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
  //params.clear()
  temp = "";
  match(tokens.at(index), "ID");
  tempId = temp;
  match(tokens.at(index), "LEFT_PAREN");
  temp = "";
  parseParameter();
  tempParam = temp;
  params.push_back(tempParam);
  parseParameterList();
  predz.setId(tempId);
  for (unsigned int i = 0; i < params.size(); ++i){
    tempParam = params.at(i);
    predz.addParam(tempParam);
  }
  params.clear();

  match(tokens.at(index), "RIGHT_PAREN");
}

void Parser::parsePredicateList(){
  //predicateList	->	COMMA predicate predicateList | lambda
  if((tokens.at(index)).gettypeOut() == "COMMA"){
    match(tokens.at(index), "COMMA");
    //params.clear();
    parsePredicate();
    predis.push_back(predz);
    predz.clearParams();
    params.clear();
    parsePredicateList();
  }
  else if((tokens.at(index)).gettypeOut() == "PERIOD"){
    return;
  }
}

void Parser::parseParameterList(){
  temp = "";
  //parameterList	-> 	COMMA parameter parameterList | lambda
  if((tokens.at(index)).gettypeOut() == "COMMA"){
    match(tokens.at(index), "COMMA");
    temp = "";
    parseParameter();
    tempParam = temp;
    params.push_back(tempParam);
    temp = "";
    parseParameterList();
    //params.clear();
  }
  else if ((tokens.at(index)).gettypeOut() == "RIGHT_PAREN"){
    return;
  }
}

void Parser::parseStringList(){
  //stringList	-> 	COMMA STRING stringList | lambda
  if((tokens.at(index)).gettypeOut() == "COMMA"){
    match(tokens.at(index), "COMMA");
    temp = "";
    match(tokens.at(index), "STRING");
    tempParam = temp;
    params.push_back(tempParam);
    // add string to domainSet
    parseStringList();
  }
  else if((tokens.at(index)).gettypeOut() == "RIGHT_PAREN"){
    return;
  }
}

void Parser::parseIdList(){
  //idList  	-> 	COMMA ID idList | lambda
  if((tokens.at(index)).gettypeOut() == "COMMA"){
    match(tokens.at(index), "COMMA");
    temp = "";
    match(tokens.at(index), "ID");
    tempParam = temp;
    params.push_back(tempParam);
    parseIdList();
  }
  else if((tokens.at(index)).gettypeOut() == "RIGHT_PAREN"){
    return;
  }
}

void Parser::parseParameter(){
  //parameter	->	STRING | ID | expression
  if((tokens.at(index)).gettypeOut() == "STRING"){
    //temp = "";
    match(tokens.at(index), "STRING");
    //tempParam = temp;
    //params.push_back(tempParam)
    return;
  }
  else if((tokens.at(index)).gettypeOut() == "ID"){
    //temp = "";
    match(tokens.at(index), "ID");
    //tempParam = temp;
    //params.push_back(tempParam)
    return;
  }
  else if((tokens.at(index)).gettypeOut() == "LEFT_PAREN"){
    parseExpression();
    return;
  }
  else if((tokens.at(index)).gettypeOut() == "COMMA" || (tokens.at(index)).gettypeOut() == "MULTIPLY" || (tokens.at(index)).gettypeOut() == "ADD" || (tokens.at(index)).gettypeOut() == "RIGHT_PAREN"){
    return;
  }
}

void Parser::parseExpression(){
  //expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
  match(tokens.at(index), "LEFT_PAREN");
  parseParameter();
  parseOperator();
  parseParameter();
  match(tokens.at(index), "RIGHT_PAREN");
  //return;
}

void Parser:: parseOperator(){
  if((tokens.at(index)).gettypeOut() == "ADD"){
    match(tokens.at(index), "ADD");
  }
  else if((tokens.at(index)).gettypeOut() == "MULTIPLY"){
    match(tokens.at(index), "MULTIPLY");
  }
  else {
    throw tokens.at(index);
  }
}


#endif
