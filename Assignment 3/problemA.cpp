// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
#define ERROR "Error: the dimensional problem occurred\n"
#define DIFF 1e-2
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
    Matrix(int n, int m, vector<vector<double>> &arr) {
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
                if(checkDoubleEquality(this->elements[i][j], 0.0)) {
                    this->setElementByIndex(i, j, 0.0);
                }
                cout<<fixed<<setprecision(PREC)<<this->elements[i][j];
                if (j != this->width - 1) cout<<" ";
                else cout<<"\n";
            }
        }
    }
    // Print the matrix and its Augmented Matrix to output
    void displayMatrixWithAugmented(Matrix* Augmented) {
        for(int i=0; i<this->height; i++) {
            for(int j=0; j<this->width*2; j++) {
                // Format is: XXXX.YY
                if(j / this->width < 1) {
                    if(checkDoubleEquality(this->elements[i][j], 0.0)) {
                        this->setElementByIndex(i, j, 0.0);
                    }
                    cout<<fixed<<setprecision(PREC)<<
                        this->elements[i][j];
                } else {
                    if(checkDoubleEquality(Augmented->elements[i][j%this->width], 0.0)) {
                        Augmented->setElementByIndex(i, j%this->width, 0.0);
                    }
                    cout<<fixed<<setprecision(PREC)<<
                        Augmented->elements[i][j%this->width];
                }
                if (j != this->width*2 - 1) cout<<" ";
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

// Column Vector
class ColumnVector : public Matrix {
public:
    ColumnVector(int n, vector<vector<double>> &arr) : Matrix(n, 1, arr) {}
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
            P = new PermutationMatrix(n, rowPos+1, j+1);
            *A = (*P)*(*A);
            // change sign of the det
            changeDeterminant = !changeDeterminant;
        }
        // Eliminate below elements from pivot
        for(int i=j+1; i<n; i++) {
            // WARNING: the real solution can think E = I
            if(!checkDoubleEquality(A->getElementByIndex(i, j), 0.0)) {
                E = new EliminationMatrix(n, i + 1, j + 1, A);
                *A = (*E) * (*A);
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

Matrix* inverseMatrix(Matrix* A) {
    const int n = A->getElements().size();
    int count = 0;
    Matrix* P;
    Matrix* E;
    // Create Augmented Matrix
    Matrix* Augmented = new IdentityMatrix(n);

    A->displayMatrixWithAugmented(Augmented);
    // Make the Matrix Upper Triangular
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
        // when pivot position should be updated
        // Permutation matrix will be needed
        if(rowPos != j) {
            P = new PermutationMatrix(n, rowPos+1, j+1);
            *A = (*P) * (*A);
            *Augmented = (*P) * (*Augmented);
        }
        // Eliminate below elements from pivot
        for(int i=j+1; i<n; i++) {
            // WARNING: the real solution can think E = I
            if(!checkDoubleEquality(A->getElementByIndex(i, j), 0.0)) {
                E = new EliminationMatrix(n, i + 1, j + 1, A);
                *A = (*E) * (*A);
                *Augmented = (*E) * (*Augmented);
            }
        }
    }
    // Make the Matrix diagonal
    for(int j=n-1; j>=0; j--) {
        // Eliminate above elements from pivot
        for(int i=j-1; i>=0; i--) {
            // WARNING: the real solution can think E = I
            if(!checkDoubleEquality(A->getElementByIndex(i, j), 0.0)) {
                E = new EliminationMatrix(n, i + 1, j + 1, A);
                *A = (*E) * (*A);
                *Augmented = (*E) * (*Augmented);
            }
        }
    }
    // Normalize Matrix
    for(int i=0; i<n; i++) {
        double c = A->getElementByIndex(i, i);
        A->setElementByIndex(i, i, 1.0);
        for(int j=0; j<n; j++) {
            Augmented->setElementByIndex(i, j,
                                         Augmented->getElementByIndex(i, j)*1.0 / c);
        }
    }
    return Augmented;
}

Matrix* solve(Matrix* A, Matrix* b, int &flag) {
    const int n = A->getElements().size();
    int count = 0;
    Matrix* P;
    Matrix* E;
    // display initial states
    // Make the Matrix Upper Triangular
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
        // when pivot position should be updated
        // Permutation matrix will be needed
        if(rowPos != j) {
            P = new PermutationMatrix(n, rowPos+1, j+1);
            *A = (*P) * (*A);
            *b = (*P) * (*b);
        }
        bool zeroDiag = false;
        if(checkDoubleEquality(A->getElementByIndex(j, j), 0.0)) zeroDiag=true;
        // Eliminate below elements from pivot
        for(int i=j+1; i<n && !zeroDiag; i++) {
            // WARNING: the real solution can think E = I
            if(!checkDoubleEquality(A->getElementByIndex(i, j), 0.0)) {
                E = new EliminationMatrix(n, i + 1, j + 1, A);
                *A = (*E) * (*A);
                *b = (*E) * (*b);
            }
        }
    }
    // Make the Matrix diagonal
    for(int j=n-1; j>=0; j--) {
        // Eliminate above elements from pivot
        bool zeroDiag = false;
        if(checkDoubleEquality(A->getElementByIndex(j, j), 0.0)) zeroDiag=true;
        for(int i=j-1; i>=0 && !zeroDiag; i--) {
            // WARNING: the real solution can think E = I
            if(!checkDoubleEquality(A->getElementByIndex(i, j), 0.0)) {
                E = new EliminationMatrix(n, i + 1, j + 1, A);
                *A = (*E) * (*A);
                *b = (*E) * (*b);
            }
        }
    }
    // Normalize Matrix
    bool zeroDiag = false;
    for(int i=0; i<n; i++) {
        // We cannot normalize Matrix which has a zero on diagonal
        if(checkDoubleEquality(A->getElementByIndex(i, i), 0.0)) zeroDiag=true;
        if(!zeroDiag) {
            double c = A->getElementByIndex(i, i);
            A->setElementByIndex(i, i, 1.0);\
            b->setElementByIndex(i, 0,
                                     b->getElementByIndex(i, 0) * 1.0 / c);
        }
    }
    
    // If there is a zero element on the diagonal (i,i)
    // and also if b(i) is also zero means there are inifinite solutions
    // else no solutions
    for(int i=0; i<n; i++) {
        if(checkDoubleEquality(A->getElementByIndex(i, i), 0.0)) {
            if(checkDoubleEquality(b->getElementByIndex(i, 0), 0.0)) {
                flag = 1; //INFINITE SOLUTIONS CASE
                return b;
            } else {
                flag = -1; // NO SOLUTION CASE
                return b;
            }
        } 
    }
        
    // ONE SOLUTION
    return b;
}


int main() {
    int n;
    Matrix* A;
    ColumnVector* b;
    Matrix* X;
    // Input Section
    cin >> n;
    vector<double> initA(n, 0.0);
    vector<vector<double>> arrA(n, initA);
    // Enter the array
    for(int i=0; i<n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arrA[i][j];
        }
    }
    // Create Matrix A
    A = new Matrix(n, n, arrA);

    // Create Column Vector b
    vector<double> initB(1, 0.0);
    vector<vector<double>> arrB(n, initB);
    // Enter the array
    for(int i=0; i<n; i++) {
        cin >> arrB[i][0];
    }
    b = new ColumnVector(n, arrB);
    // Track the matrix and solve it
    int flag = 0;
    X = solve(A, b, flag);
    // Output
    if(flag==1) {
        cout<<"INF"; // INFINITE SOLUTIONS
    } else if(flag==-1) {
        cout<<"NO"; // NO SOLUTION
    } else X->displayMatrix(); // ONE SOLUTION
    return 0;
}
