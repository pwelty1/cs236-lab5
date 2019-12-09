#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

//#include "Scanner.h"

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK,LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED,
EOFTOKEN};

class Token {
    private:
        string typeOut;
        string value;
        int lineNum;
    public:
        void token(TokenType t, int num, string temp);
        void toString();
        string getValue();
        string gettypeOut();

};


void Token::token(TokenType t, int Num, string temp = "") {
    lineNum = Num;
    switch(t) {
        case COMMA:
            typeOut = "COMMA";
            value = ",";
            break;
        case PERIOD:
            typeOut = "PERIOD";
            value = ".";
            break;
        case Q_MARK:
            typeOut ="Q_MARK";
            value = "?";
            break;
        case LEFT_PAREN:
            typeOut ="LEFT_PAREN";
            value = "(";
            break;
        case RIGHT_PAREN:
            typeOut ="RIGHT_PAREN";
            value = ")";
            break;
        case COLON:
            typeOut ="COLON";
            value = ":";
            break;
        case COLON_DASH:
            typeOut ="COLON_DASH";
            value = ":-";
            break;
        case MULTIPLY:
            typeOut ="MULTIPLY";
            value = "*";
            break;
        case ADD:
            typeOut ="ADD";
            value = "+";
            break;
        case SCHEMES:
            typeOut ="SCHEMES";
            value = "Schemes";
            break;
        case FACTS:
            typeOut ="FACTS";
            value = "Facts";
            break;
        case RULES:
            typeOut ="RULES";
            value = "Rules";
            break;
        case QUERIES:
            typeOut ="QUERIES";
            value = "Queries";
            break;
        case ID:
            typeOut = "ID";
            value = temp;
            break;
        case STRING:
            typeOut ="STRING";
            value = temp;
            break;
        case COMMENT:
            typeOut ="COMMENT";
            value = temp;
            break;
        case UNDEFINED:
            typeOut ="UNDEFINED";
            value = temp;
            break;
        case EOFTOKEN:
            typeOut ="EOF";
            value = "";
            break;
    }
    ;
}

string Token::getValue() {
    return value;
}

string Token::gettypeOut() {
    return typeOut;
}

void Token::toString() {
    cout << "(" << gettypeOut() << ",\"" << value << "\","<< lineNum << ")" << endl;
}



#endif
