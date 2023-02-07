/*
  Problem:
  Write same calculator without branching but with functions. Make possible to add, subtract letters such that (no divisions )
  
  Test cases:
  input >--> output
  a,b,+ >--> ab
  abb,b,- >--> ab
  aba,b,- >--> error message
  Make possible to multiply words on integers such that
  abc,2,* >--> abcabc
*/

// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ERROR "error message"

ll toInt(string str){
    // convert String to Integer
    ll n=0;
    for(char i:str){
        n*=10;
        n+=ll(i-'0');
    }
    return n;
}

bool isNumber(char c) {
    // check the letter is number or not
    if(c >= '0' && c <= '9') return true;
    return false;
}

void makeSplit(string line, string& str_1, string& str_2, char& oper, char operators[3]) {
    // counter
    ll cnt = 1;
    // temporary string
    string temp = "";
    // iterate through text
    bool isOperator = false;
    for(ll i=0; i<line.size(); i++) {
        if(line[i]==',') {
            if(cnt==1){
                str_1 = temp;
                temp = "";
                cnt++;
            }
            continue;
        }
        // check if char is operator
        for(int j=0; j<3; j++) {
            if(line[i] == operators[j]) {
                // specify operator type
                oper = operators[j];
                isOperator = true;
                continue;
            }
        }
        // operator -> ignore
        if(isOperator) {
            isOperator = false;
            continue;
        }
        // add to temporary string
        temp += line[i];
    }
    // the second part is left
    str_2 = temp;
}

string subtractString(string str_1, string str_2) {
    if(str_2.size() > str_1.size()) return ERROR;
    bool isSuffix = true;
    for(int i=1; i<=str_2.size(); i++) {
        //compare every element starting from back
        isSuffix &= (str_2[str_2.size()-i] == str_1[str_1.size()-i]);
    }

    if(isSuffix) {
        // abcde - de = abc
        string res = "";
        for(int i=0; i<str_1.size()-str_2.size(); i++) {
            res += str_1[i];
        }
        return res;
    }
    return ERROR;
}

bool isDecimal(string str) {
    for(char letter:str) {
        if(!isNumber(letter)) return false;
    }
    return true;
}

string multiplyString(string str_1, string str_2) {
    // check wether str_2 is decimal
    // ab*2=abab,  bc*as=error
    // REMINDER: I didn't consider exponential case ab*1e3
    if(isDecimal(str_2)) {
        string res = "";
        for(ll i=0; i<toInt(str_2); i++) {
            res += str_1;
        }
        return res;
    }
    return ERROR;
}

string switchCalculator(string str_1, string str_2, char oper) {
    // TODO: consider each cases
    switch(oper) {
        case '+':
            // add
            return str_1 + str_2;
        case '-':
            //subtract suffix
            return subtractString(str_1, str_2);
        case '*':
            // multiply by number
            return multiplyString(str_1, str_2);
        default:
            // error operator type
            return ERROR;
    }
}

int main() {
    ifstream inFile ("input.txt");
    string line, result, str_1, str_2;
    char oper;
    char operators[3] = {'+', '-', '*'};

    // input
    getline(inFile, line);
    // Main Algorithm function
    makeSplit(line, str_1, str_2, oper, operators);
    result = switchCalculator(str_1, str_2, oper);
    //cout<<str_1<<endl<<oper<<endl<<str_2;

    // output
    ofstream myfile;
    myfile.open ("output.txt");
    myfile << result;
    myfile.close();
    return 0;
}
