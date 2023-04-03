// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
#define ERROR "Error: the dimensional problem occurred\n"
#define DIFF 1e-6

bool checkDoubleEquality(double a, double b) {
    if(abs(a-b) <= DIFF) return true; // equal
    else return false; // not equal
}

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
        vector<double> init(m, 0);
        vector<vector<double>> empty(n, init);
        this->elements = empty;
    }
    Matrix(int n, int m, vector<vector<double>> arr) {
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
    vector<vector<double>> getElements() {
        return this->elements;
    }
    void setElementByIndex(int i, int j, double val) {
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
            for(int j=0; j<this->width; j++) {
                if (checkDoubleEquality(this->elements[i][j], int(this->elements[i][j])))
                    result += to_string(int(this->elements[i][j]));
                else result += to_string(this->elements[i][j]);
                if (j != this->width - 1) result += " ";
                else result += "\n";
            }
        }
    }
    int height;
    int width;
    vector<vector<double>> elements;
};

// Identity Matrix
class IdentityMatrix : public Matrix {
public:
    IdentityMatrix(int n) : Matrix(n, n) {
        for (int i = 0; i < n; i++) {
            elements[i][i] = 1;
        }
    }
};

// Elimination Matrix
class EliminationMatrix : public Matrix {
public:
    EliminationMatrix(int n, int iRow, int jCol, Matrix* A) : Matrix(n, n) {
        bool flag = true;
        // zero indexing
        iRow--;
        jCol--;
        // First make it Identity Matrix
        for(int ind = 0; ind < n; ind++) {
            elements[ind][ind] = 1.0;
        }
        if(!checkDoubleEquality(A->getElementByIndex(iRow, jCol), 0.0)){
            flag = false;
        }
        // We need to find vertical element
        // not to be zero
        if(!flag) {
            if(!checkDoubleEquality(A->getElementByIndex(jCol, jCol), 0.0)) {
                elements[iRow][jCol] =
                        - double(A->getElementByIndex(iRow, jCol)*1.0 / A->getElementByIndex(jCol, jCol));
            } else {
                // row2 j is zero therefore we cannot nullify row1 j
            }
        } else {
            // Row1 is filled with 0s
        }
    }
};

// Permutation Matrix
class PermutationMatrix : public Matrix {
public:
    PermutationMatrix(int n, int row1, int row2) : Matrix(n, n) {
        row1--;
        row2--;
        for (int i = 0; i < n; i++) {
            elements[i][i] = 1;
        }
        swap(elements[row1], elements[row2]);
    }
};

int main() {
    int n;
    string result = "";
    Matrix* A;
    IdentityMatrix* I;
    PermutationMatrix* P;
    
    // Input Section
    cin >> n;
    Matrix* B = new Matrix(n, n);
    Matrix* C = new Matrix(n, n);
    vector<double> init(n, 0.0);
    vector<vector<double>> arr(n, init);
    // Enter the array
    for(int i=0; i<n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    // Create Matrix A, B and C
    A = new Matrix(n, n, arr);
    // TODO: create Identity Matrix
    I = new IdentityMatrix(3);
    I->displayMatrix(result);
    // TODO: create Elimination Matrix
    EliminationMatrix* E = new EliminationMatrix(n, 2, 1, A);
    E->displayMatrix(result);
    // TODO: create new B matrix which is multiplication of E and A
    *B = (*E)*(*A);
    B->displayMatrix(result);
    // TODO: create Permutation Matrix
    P = new PermutationMatrix(n, 2, 1);
    P->displayMatrix(result);
    // TODO: create new C matrix which is multiplication of P and A
    *C = (*P)*(*A);
    C->displayMatrix(result);
    // Output
    cout << result;
    return 0;
}
