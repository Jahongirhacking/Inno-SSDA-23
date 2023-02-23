// Jahongir Hayitov CS-01
#include <bits/stdc++.h>
using namespace std;
#define ERROR "Error: the dimensional problem occurred\n"

class Matrix {
public:
    Matrix() {
        this->width = 0;
        this->height = 0;
        this->elements = {};
    }
    Matrix(int n, int m) {
        this->height = n;
        this->width = m;
        vector<int> init(m, 0);
        vector<vector<int>> empty(n, init);
        this->elements = empty;
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
    void setElementByIndex(int i, int j, int val) {
        this->elements[i][j] = val;
    }
    int getElementByIndex(int i, int j) {
        return this->elements[i][j];
    }

    // Assign Operator
    void operator = (Matrix M) {
        this->height = M.getElements().size();
        this->width = M.getElements()[0].size();
        this->elements = M.getElements();
    }

    // Addition operation
    Matrix operator + (Matrix M) {
        Matrix sumMatrix = Matrix(this->height, this->width, this->elements);
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width; j++) {
                sumMatrix.setElementByIndex(i, j,sumMatrix.getElementByIndex(i, j) + M.getElementByIndex(i, j));
            }
        }
        return sumMatrix;
    }

    // Subtraction operation
    Matrix operator - (Matrix M) {
        Matrix difMatrix = Matrix(this->height, this->width, this->elements);
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width; j++) {
                difMatrix.setElementByIndex(i, j,difMatrix.getElementByIndex(i, j) - M.getElementByIndex(i, j));
            }
        }
        return difMatrix;
    }

    // Multiplication Operation
    Matrix operator * (Matrix M) {
        Matrix multMatrix = Matrix(this->height, M.getWidth());
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<M.getWidth(); j++) {
                // compute each element with multiplication and sum
                for(int k=0; k<this->width; k++) {
                    multMatrix.setElementByIndex(i, j,multMatrix.getElementByIndex(i, j)
                    + this->elements[i][k] * M.getElementByIndex(k, j));
                }
            }
        }
        return multMatrix;
    }

    // Transpose Matrix
    Matrix matrixTranspose() {
        Matrix transposeMatrix = Matrix(this->width, this->height);
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width; j++) {
                transposeMatrix.setElementByIndex(j, i, this->elements[i][j]);
            }
        }
        return transposeMatrix;
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

void activateMatrix(int k, Matrix temp, Matrix& A, Matrix& B, Matrix& C) {
    switch (k) {
        case 0:
            A = temp;
            break;
        case 1:
            B = temp;
            break;
        case 2:
            C = temp;
            break;
    }
    return;
}

int main() {
    ifstream inFile ("input.txt");
    int n=0, m=0;
    string result = "";
    Matrix A;
    Matrix B;
    Matrix C;

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
        Matrix temp = Matrix(n, m, arr);
        // Create Matrix A, B and C
        activateMatrix(k, temp, A, B, C);
    }

    // Addition A+B
    if(A.getWidth() == B.getWidth() && A.getHeight() == B.getHeight()) {
        Matrix D = (A + B);
        D.displayMatrix(result);
    } else {
        result += ERROR;
    }
    // Subtraction B-A
    if(A.getWidth() == B.getWidth() && A.getHeight() == B.getHeight()) {
        Matrix E = (B - A);
        E.displayMatrix(result);
    } else {
        result += ERROR;
    }
    // Multiplication C*A
    if(C.getWidth() == A.getHeight()) {
        Matrix F = (C * A);
        F.displayMatrix(result);
    } else {
        result += ERROR;
    }
    // Transpose A
    Matrix G = (A.matrixTranspose());
    G.displayMatrix(result);
    
    // Output
    ofstream myFile;
    myFile.open ("output.txt");
    myFile << result;
    myFile.close();
    return 0;
}
