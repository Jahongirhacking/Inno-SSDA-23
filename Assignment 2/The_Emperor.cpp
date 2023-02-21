// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

/**
 *  | Solution Approach |
 *  Given in the task, The poison affect to the victim in 20-40 hours,
 *  But We have 48 hours, therefore we take max(20, 40) = 40 for our analysis.
 *  This means we have only 1 attempt to take minimum punished inmates,
 *  We have 2 base cases: 0 and 1
 *  If we have 0 flagon -> there is no poison,
 *  If we have 1 flagon -> it's a poison, In these cases we don't need any inmate
 *  Let's assume we have 3 flagons:
 *  * and we have 1 inmate, for simplicity we can express his condition with 0(die) and 1(alive),
 *    Then there are 2 cases {0, 1} he is either died or alive,
 *    it's not enough to detect 1 poison among 3 flagons,
 *  * Therefore we try with 2 inmates:
 *    Then there are 4 cases {00, 01, 10, 11},
 *    1) Both of them are died, 2) first is died, second is alive,
 *    3) second is died, first is alive, 4) both of them are alive
 *    We can detect the poison in this way;
 *
 *  | Solution |
 *  We need to find x, and the number of all subsets with length x,
 *  which is (2^x) >= N such that (2^(x-1)) < N
 *  We can find it by using for loop or using math log2 and rounding operations
 */

int main() {
    ifstream inFile ("input.txt");
    ull n;
    ull result = 0;
    // input
    inFile >> n;
    // solution
    bool isOddExist = false;
    // Find the ceil of log2(n)
    while(n>1) {
        isOddExist |= n%2;
        result++;
        n /= 2;
    }
    if(isOddExist) result++;
    // output the result
    ofstream outFile;
    outFile.open ("output.txt");
    outFile << result;
    outFile.close();
    return 0;
}
