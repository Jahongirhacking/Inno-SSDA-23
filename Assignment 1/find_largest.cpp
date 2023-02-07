/*
  First largest single integer using pointers
  Problem:
  - You have a String S containing N<100 elements with no spaces (letters, numbers, etc). Write a C++ program to find the first largest single integer (one digit
  number [-9,9] ) that occurs in this string and then print it, and its index in the string using pointers/functions that have parameters as pointers or references.
  here you can see examples:
  - notice in the first example you have 2 fives, you take the first one
  - and its index starts from: 0 for ‘w’.
  - display the message ‘-1’ if you don’t find numbers in the string.
  - for the negative integers print the index of the integer itself like in the second example(without the minus).

*/

// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

bool isNumber(char c) {
    // check the letter is number or not
    if(c >= '0' && c <= '9') return true;
    return false;
}

void findLargest(char* ch, ll& maxVal, ll& maxPos) {
    // iterate through the text
    for(ll i=0; *(ch+i)!='\0'; i++) {
        // if there exist any number
        if(isNumber(*(ch+i))) {
            ll val = *(ch+i) - '0';
            // check it has previous minus elem.
            if(i!=0 && *(ch+i-1)=='-') {
                val = -val;
            }
            // check the number is greater than current max
            if(val > maxVal) {
                // update maxVal
                maxVal = val;
                // set the position to max
                maxPos = i;
            }
        }
    }
}

int main() {
    ifstream inFile ("input.txt");
    string line, result;
    // initialize max to lower bound of [-9, 9]
    ll maxVal = -10, maxPos = -1;
    // input
    getline(inFile, line);

    // Main Algorithm function
    findLargest(&(line[0]), maxVal, maxPos);

    if(maxPos == -1) {
        // if there is no number in the string
        result = "-1";
    } else {
        result = to_string(maxVal);
        result += ",";
        result += to_string(maxPos);
    }
    // output
    ofstream myfile;
    myfile.open ("output.txt");
    myfile << result;
    myfile.close();
    return 0;
}
