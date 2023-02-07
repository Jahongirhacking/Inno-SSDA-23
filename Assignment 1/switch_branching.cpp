/*
    Switch - branching
  Problem:
  - Become familiar with switch-branching (Just Google it)
  - Using this branching, write a calculator such that user inputs number_1, number_2 (-1e8 <= number_1,number_2 <= 1e8) and operator separated by comma. For example:
  - 2, 5, + The code should return 7
  - Prevent division by zero!
*/

// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

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

ll valueExponential(string str) {
    string part = "";
    for(ll i = 0; i < str.size(); i++) {
        // if the input is exponential
        if(str[i] == 'e') {
            ll mult = toInt(part);
            part = "";
            // next to the e letter
            // until the end
            i++;
            for(; i < str.size() && isNumber(str[i]); i++) {
                part += str[i];
            }
            // power of the ten
            ll power = toInt(part);
            return mult*pow(10, power);
        }
        part += str[i];
    }
    return toInt(str);
}

int main() {
    ifstream inFile ("input.txt");
    string line, number_1, number_2, result;
    char operation;
    ll num1, num2;
    // input
    getline(inFile, line);
    // operation type: * - / +
    operation = line[line.size() - 1];
    ll cnt = 1;
    for(char i:line) {
        if(i == ',') {
            // split the string
            if(cnt == 2) break;
            cnt++;
        }
        if(cnt == 1) {
            // for number_1
            if(isNumber(i)) number_1 += i;
        } else {
            // for number_2
            if(isNumber(i)) number_2 += i;
        }
    }
    num1 = valueExponential(number_1);
    num2 = valueExponential(number_2);

    // TODO: consider each case
    switch(operation){
        case '+':
            // add
            result = to_string(num1 + num2);
            break;
        case '-':
            // subtract
            result = to_string(num1 - num2);
            break;
        case '*':
            // multiply
            result = to_string(num1 * num2);
            break;
        case '/':
            // divide
            if(num2 == 0) {
                // division by zero = NAN
                result = "NAN";
                break;
            }
            result = to_string(num1 / num2);
            break;
        default:
            // invalid operation type
            result = "NAN";
    }

    // output
    ofstream myfile;
    myfile.open ("output.txt");
    myfile << result;
    myfile.close();
    return 0;
}
