// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
#define ERROR "Error: the dimensional problem occurred\n"

class Matrix {
public:
    Matrix() {}
    Matrix(int n, int m) {
        this->height = n;
        this->width = m;
    }
    Matrix(int n, int m, vector<vector<int>> arr) {
        this->elements = arr;
        this->height = n;
        this->width = m;
    }
    int getHeight() {
        return this->height;
    }
    int getWidth() {
        return this->width;
    }
    vector<vector<int>> getElements() {
        return this->elements;
    }
    void assignMatrix(vector<vector<int>> arr) {
        this->elements = arr;
    }
    // Addition operation
    vector<vector<int>> matrixAddition(Matrix* M) {
        vector<vector<int>> sum = this->elements;
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width; j++) {
                sum[i][j] += (M->getElements())[i][j];
            }
        }
        return sum;
    }
    // Subtraction Operation
    vector<vector<int>> matrixSubtraction(Matrix* M) {
        vector<vector<int>> dif = this->elements;
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width; j++) {
                dif[i][j] -= (M->getElements())[i][j];
            }
        }
        return dif;
    }
    // Multiplication Operation
    vector<vector<int>> matrixMultiplication(Matrix* M) {
        vector<int> init(M->getWidth(), 0);
        vector<vector<int>> mul(this->height, init);
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<M->getWidth(); j++) {
                int sum = 0;
                // compute each element with multiplication and sum
                for(int k=0; k<this->width; k++) {
                    sum += this->elements[i][k] * (M->getElements())[k][j];
                }
                mul[i][j] = sum;
            }
        }
        return mul;
    }
    // Transpose Matrix
    vector<vector<int>> matrixTranspose() {
        vector<int> init(this->height, 0);
        vector<vector<int>> transpose(this->width, init);
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width; j++) {
                transpose[j][i] = this->elements[i][j];
            }
        }
        return transpose;
    }

    // Print the matrix elements to output
    void displayMatrix(string &result) {
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width-1; j++) {
                result += to_string(this->elements[i][j]);
                result += " ";
            }
            result += to_string(this->elements[i][width-1])+"\n";
        }
    }
private:
    int height;
    int width;
    vector<vector<int>> elements;
};

int main() {
    ifstream inFile ("input.txt");
    int n, m;
    string result = "";
    Matrix* A;
    Matrix* B;
    Matrix* C;

    for(int k=0; k<3; k++) {
        inFile >> n >> m;
        vector<int> init(m, 0);
        vector<vector<int>> arr(n, init);
        // Input Array
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                inFile >> arr[i][j];
            }
        }
        // Create Matrix A, B and C
        switch (k) {
            case 0:
                A = new Matrix(n, m, arr);
                break;
            case 1:
                B = new Matrix(n, m, arr);
                break;
            case 2:
                C = new Matrix(n, m, arr);
                break;
        }
    }

    vector<vector<int>> temp;
    // Addition A+B
    if(A->getWidth() == B->getWidth() && A->getHeight() == B->getHeight()) {
        temp = A->matrixAddition(B);
        Matrix* D = new Matrix(A->getHeight(), A->getWidth(), temp);
        D->displayMatrix(result);
    } else {
        result += ERROR;
    }
    // Subtraction B-A
    if(A->getWidth() == B->getWidth() && A->getHeight() == B->getHeight()) {
        temp = B->matrixSubtraction(A);
        Matrix* E = new Matrix(A->getHeight(), A->getWidth(), temp);
        E->displayMatrix(result);
    } else {
        result += ERROR;
    }
    // Multiplication C*A
    if(C->getWidth() == A->getHeight()) {
        temp = C->matrixMultiplication(A);
        Matrix* F = new Matrix(C->getHeight(), A->getWidth(), temp);
        F->displayMatrix(result);
    } else {
        result += ERROR;
    }
    // Transpose A
    temp = A->matrixTranspose();
    Matrix* G = new Matrix(A->getWidth(), A->getHeight(), temp);
    G->displayMatrix(result);

    ofstream myFile;
    myFile.open ("output.txt");
    myFile << result;
    myFile.close();
    return 0;
}
