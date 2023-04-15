// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
#define ERROR "Error: the dimensional problem occurred\n"
#define DIFF 1e-6
#define PREC 2

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
    double getElementByIndex(int i, int j) {
        return this->elements[i][j]*1.0;
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
                    multMatrix.setElementByIndex(i, j,multMatrix.getElementByIndex(i, j)*1.0
                    + this->elements[i][k]*1.0 * M.getElementByIndex(k, j));
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
    void displayMatrix() {
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width; j++) {
                // Format is: XXXX.YY
                cout<<fixed<<setprecision(PREC)<<this->elements[i][j];
                if (j != this->width - 1) cout<<" ";
                else cout<<"\n";
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

double findDeterminant(Matrix* A) {
    int count = 1;
    int n = A->getElements().size();
    EliminationMatrix* E = nullptr;
    PermutationMatrix* P = nullptr;
    bool changeDeterminant = false;
    // Check and make permutation that there is no zero in diagonal
    double maxElem;
    for(int j=0; j<n; j++) {
        maxElem = A->getElementByIndex(j, j);
        int rowPos = j;
        for(int i=j; i<n; i++) {
            // WARNING: Rounding Error may occur
            if(abs(A->getElementByIndex(i, j)) > maxElem) {
                maxElem = abs(A->getElementByIndex(i, j));
                rowPos = i;
            }
        }
        // If max elem is 0 then det = 0
        if(checkDoubleEquality(maxElem, 0.0)) return 0.0;
        // when pivot position should be updated
        // Permutation matrix will be needed
        if(rowPos != j) {
            cout<<"step: permutation\n";
            P = new PermutationMatrix(n, rowPos+1, j+1);
            *A = (*P)*(*A);
            // change sign of the det
            changeDeterminant = !changeDeterminant;
            A->displayMatrix();
        }
        // Eliminate below elements from pivot
        for(int i=j+1; i<n; i++) {
            // WARNING: the real solution can think E = I
            if(!checkDoubleEquality(A->getElementByIndex(i, j), 0.0)) {
                cout<<"step: elimination\n";
                E = new EliminationMatrix(n, i + 1, j + 1, A);
                *A = (*E) * (*A);
                A->displayMatrix();
            }
        }
    }
    // Calculate the Determinant for U form
    double det = 1.0;
    for(int i=0; i<n; i++) {
        det *= A->getElementByIndex(i, i);
    }
    if(changeDeterminant) return -det;
    return det;
}

int main() {
    int n;
    Matrix* A;
    // Input Section
    cout << "Input the dimensions of a matrix:\nn: ";
    cin >> n;
    vector<double> init(n, 0.0);
    vector<vector<double>> arr(n, init);
    cout << "Input n*n elements of a matrix:\n"; 
    // Enter the array
    for(int i=0; i<n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    // Create Matrix A
    A = new Matrix(n, n, arr);
    // Track the matrix and Calculate the determinant
    double det = findDeterminant(A);
    cout<<"result:\n";
    // Format XXXX.YY
    cout<<fixed<<setprecision(PREC)<<det;
    return 0;
}
