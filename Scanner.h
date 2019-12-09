#ifndef SCANNER
#define SCANNER

#include <iostream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <locale>

#include "Token.h"

using namespace std;



class Scanner {

    private:
        string filename;
        vector<Token> tokens;
        int lineCtr = 1;

    public:
        Scanner(string inputFile);
        void readFile();
        void tokenize(string temp1, int lineNum, string safetyTemp);
        int getNumTkns() { return tokens.size();}
        int getLineNum() {return lineCtr;}
        vector<Token> getTokens(){return tokens;}

};

Scanner::Scanner(string inputFile) {
    filename = inputFile;
    readFile();
}

void Scanner::tokenize(string temp1,int lineNum, string safetyTemp = "") {
    TokenType type;
    char temp7=' ';
    Token newToken;
    if (temp1.size()== 1){

        temp7 = temp1[0];
    }

        if (temp1 == ","){
            type = COMMA;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "."){
            type = PERIOD;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "?"){
            type = Q_MARK;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "("){
            type = LEFT_PAREN;
            newToken.token(type,lineNum);
            }
        else if (temp1 == ")"){
            type = RIGHT_PAREN;
            newToken.token(type,lineNum);
            }
        else if (temp1 == ":"){
            type = COLON;
            newToken.token(type,lineNum);
            }
        else if (temp1 == ":-"){
            type = COLON_DASH;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "*"){
            type = MULTIPLY;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "+"){
            type = ADD;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "Schemes"){
            type = SCHEMES;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "Facts"){
            type = FACTS;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "Rules"){
            type = RULES;
            newToken.token(type,lineNum);
            }
        else if (temp1 == "Queries"){
            type = QUERIES;
            newToken.token(type,lineNum);
            }
        else if (isalpha(temp7)) {
            type = ID;
            newToken.token(type,lineNum, safetyTemp);
            }
        else if (temp1 == "\'"){
            type= STRING;
           newToken.token(type,lineNum, safetyTemp);
            }
        else if (temp1 == "\n"){
            type =COMMENT;
           newToken.token(type,lineNum, safetyTemp);
            }
        else if (temp1 == "#"){
            type =COMMENT;
            newToken.token(type,lineNum, safetyTemp);
            }
        else if (temp1 == ""){
            type = EOFTOKEN;
            newToken.token(type,lineNum);
            }
        else{
            type = UNDEFINED;
           newToken.token(type,lineNum, safetyTemp);
            }
    //newToken.toString();
    tokens.push_back(newToken);
}

void Scanner::readFile(){

    ifstream in;
    in.open(filename);
    //int count = 0;
    //cout<< lineCtr << " 0"<<  endl;
    char c1;
    while (in.peek() != EOF) { // end of file token always pops out after this loop.
        //cout << "Hey we are right here" << endl;
        in.get(c1);
        if (c1 == '\n') {
            ++lineCtr;
            //cout<< lineCtr << " 1"<<  endl;
            continue;
        }
        else if (c1 == (' ')|| c1 == ('\t')) {
            //cout << "space" << endl;
            continue;
        }
        else if (c1 =='\''){  // State Machine for STRING token
            int count2 = 0;
            //cout<< c1 << endl;
            string temp2;
            temp2 += c1;
            //cout << c1 <<"Is there a space?" << "0"<< endl;
            //cout << "Warning flag1" << endl;
            while (in.get(c1)){
                //cout << c1 <<"Is there a space?" << endl;
                if ((c1 == '\'') && (in.peek() == '\'')) {
                    //cout << c1 <<"Is there a space?" << "0"<< endl;
                    temp2 += c1;
                    in.get(c1);
                    //cout << c1 <<"Is there a space?" << "0"<< endl;
                    temp2+= c1;
                    //if ()
                    continue;
                }
                else if ( c1 == '\'' && in.peek()!= '\''){
                     //cout << c1 <<"Is there a space?" << "1"<< endl;
                    break;
                }
                else if (c1  == '\n') {
                    temp2 += c1;
                    ++count2;
                     //cout << c1 <<"Is there a space?" << "2"<< endl;
                    continue;
                }
                //else if (c1 ==' ' | c1 =='\t'){
                    //temp2 += c1;
                     //cout << c1 <<"Is there a space?" << "3"<< endl;
                //}
                else{
                    //if (isspace(c1)){
                       //temp2 += ' ';
                       //continue;
                    //}
                    temp2 += c1;
                    //cout << c1 <<"Is there a space?" << "4 "<< endl;
                }
            }
            //cout << temp2 << endl;
            if (in.eof()){
                //cout<< lineCtr << "2" << endl;
                tokenize(temp2, lineCtr, temp2);
                lineCtr += count2;
                break;
            }
            temp2 += c1;
            string temp8;
            temp8 += c1;
            tokenize(temp8,lineCtr, temp2);
            lineCtr += count2;
            //cout<< lineCtr << "3" << endl;

            continue;

        }
        else if (isalpha(c1)) {   //state machine for ID tokens
            //cout << c1 << endl;
            string temp3;
            if (c1 =='F') {       //state machine for FACTS

                temp3 += c1;
                in.get(c1);
                if (c1 =='a') {

                    temp3 += c1;
                    in.get(c1);
                    if (c1 == 'c') {

                        temp3 += c1;
                        in.get(c1);
                        if (c1 =='t') {

                            temp3 += c1;
                            in.get(c1);
                            if (c1 =='s') {

                                temp3 += c1;
                               if(!(isalnum(in.peek()))){
                                            tokenize(temp3, lineCtr);
                                            continue;
                                        }
                                        in.get(c1);
                            }
                        }
                    }
                }
            }
            else if (c1 =='Q') {       //state machine for QUERIES

                temp3 += c1;
                in.get(c1);
                if (c1 =='u') {

                    temp3 += c1;
                    in.get(c1);
                    if (c1 =='e') {

                        temp3 += c1;
                        in.get(c1);
                        if (c1 =='r') {

                            temp3 += c1;
                            in.get(c1);
                            if (c1 =='i') {

                                temp3 += c1;
                                in.get(c1);
                                if (c1 =='e') {

                                    temp3 += c1;
                                    in.get(c1);
                                    if (c1 =='s') {

                                        temp3 += c1;
                                        if(!(isalnum(in.peek()))){
                                            tokenize(temp3, lineCtr);
                                            continue;

                                        }
                                        in.get(c1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (c1 =='R') {       //state machine for Rules
                temp3 += c1;
                in.get(c1);
                if (c1 =='u') {

                    temp3 += c1;
                    in.get(c1);
                    if (c1 =='l') {

                        temp3 += c1;
                        in.get(c1);
                        if (c1 =='e') {

                            temp3 += c1;
                            in.get(c1);
                            if (c1 =='s') {

                                temp3 += c1;
                                if(!(isalnum(in.peek()))){
                                            tokenize(temp3, lineCtr);
                                            continue;
                                        }
                                in.get(c1);
                            }
                        }
                    }
                }
            }
            else if (c1 =='S') {       //state machine for SCHEMES

                temp3 += c1;
                in.get(c1);
                if (c1 =='c') {

                    temp3 += c1;
                    in.get(c1);
                    if (c1 =='h') {

                        temp3 += c1;
                        in.get(c1);
                        if (c1 =='e') {

                            temp3 += c1;
                            in.get(c1);
                            if (c1 =='m') {

                                temp3 += c1;
                                in.get(c1);
                                if (c1 =='e') {

                                    temp3 += c1;
                                    in.get(c1);
                                    if (c1 =='s') {

                                        temp3 += c1;
                                        //if (in.peek(=='s')){
                                            //;
                                        //}
                                        if(!(isalnum(in.peek()))){
                                            tokenize(temp3, lineCtr);
                                            continue;
                                        }
                                        in.get(c1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //in.get(c1);
            //cout << temp3 << endl;
            while(isalnum(c1)){
                temp3 += c1;
                in.get(c1);
                if(!(isalnum(c1))){
                    break;
                }
            }
            //cout << temp3 << "done" << endl;
            string c2;
            if (!(isalnum(c1))){
                c2 = "a";
            }
            in.putback(c1);
            tokenize(c2,lineCtr, temp3);
            continue;
        }
        else if (c1 == '#'){ //state machine for COMMENT

            string temp4;
            temp4 += c1;
            int count1 = 0;
            //cout << temp4 << endl;
            in.get(c1);
            if (c1 == '|') { //multiline
                temp4 += c1;
                while(in.get(c1)){
                    if(c1 =='\n'){
                        temp4 += c1;
                        ++count1;
                        continue;
                    }
                    else if (c1  == '|' && in.peek()== '#'){
                        temp4 += c1;
                        in.get(c1);
                        temp4 += c1;
                        string c3;
                        c3 = c1;
                        tokenize(c3,lineCtr,temp4);
                        break;
                    }
                    else {
                        temp4 += c1;
                    }
                }
                if(in.eof()) {
                    //cout<< lineCtr << "3" << endl;
                    tokenize(temp4, lineCtr, temp4);
                    lineCtr += count1;
                    break;
                }
            lineCtr += count1;
            }
             //cout<< lineCtr << "1" << endl;
            //cout << temp4 << endl;
            else {
                while (c1  != '\n') { //single-line
                temp4 += c1;
                in.get(c1);
                }
                //cout<< temp4<< endl;
                if(in.eof()) {
                    //cout<< lineCtr << "1" << endl;
                    string temp10 = "\n";
                    tokenize(temp10, lineCtr,temp4);
                   //++lineCtr;
                    break;
                }
                else{
                string c4;
                c4 += c1;
                tokenize(c4, lineCtr, temp4);
                ++lineCtr;
                }

            }

        }
        else if (c1 == (',')|| c1 == ('.')|| c1 == ('?')|| c1 == ('(')|| c1 == (')')|| c1 == (':')|| c1 == ('*')||c1 == ('+') ){ // state machine for all 1 digit chars chars
            string temp5;
            temp5+= c1;
            if (in.peek() == '-'&& c1 == ':'){ // specific state machine for COLON_DASH
                in.get(c1);
                temp5+= c1;
                tokenize(temp5, lineCtr);
                continue;

            }
            else {
                tokenize(temp5, lineCtr);
                continue;
            }
        }
        else {// State machine for undefined
            string temp9;
            temp9 += c1;

            //cout << temp9 << endl;
            tokenize(temp9 ,lineCtr,temp9);

        }

    } // eof
    string temp6 = "";
    tokenize(temp6, lineCtr);




    return;
}

#endif
