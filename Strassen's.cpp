#include <iostream>
#include <vector>

using namespace std;

// Function to add two matrices
vector<vector<int > > add(vector<vector<int> > A, vector<vector<int> > B) {
    int n = A.size();
    vector<vector<int > > C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Function to subtract two matrices
vector<vector<int > > subtract(vector<vector<int > > A, vector<vector<int > > B) {
    int n = A.size();
    vector<vector<int > > C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Function to multiply two matrices
vector<vector<int > > multiply(vector<vector<int > > A, vector<vector<int > > B) {
    int n = A.size();
    vector<vector<int > > C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Function to split a matrix into four quadrants
void split(vector<vector<int > > A, vector<vector<int > >& A11, vector<vector<int > >& A12, vector<vector<int > >& A21, vector<vector<int > >& A22) {
    int n = A.size()/2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+n];
            A21[i][j] = A[i+n][j];
            A22[i][j] = A[i+n][j+n];
        }
    }
}

// Function to join four quadrants into a matrix
vector<vector<int > > join(vector<vector<int> > A11, vector<vector<int > > A12, vector<vector<int > > A21, vector<vector<int > > A22) {
    int n = A11.size()*2;
    vector<vector<int > > A(n, vector<int>(n, 0));
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            A[i][j] = A11[i][j];
            A[i][j+n/2] = A12[i][j];
            A[i+n/2][j] = A21[i][j];
            A[i+n/2][j+n/2] = A22[i][j];
        }
    }
    return A;
}

// Function to perform Strassen's matrix multiplication
vector<vector<int > > strassen(vector<vector<int > > A, vector<vector<int > > B) {
    int n = A.size();
    vector<vector<int > > C(n, vector<int>(n, 0));
    
    // Base case
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Splitting the matrices into quadrants
    vector<vector<int > > A11(n/2, vector<int>(n/2)), A12(n/2, vector<int>(n/2)), A21(n/2, vector<int>(n/2)), A22(n/2, vector<int>(n/2));
    vector<vector<int> > B11(n/2, vector<int>(n/2)), B12(n/2, vector<int>(n/2)), B21(n/2, vector<int>(n/2)), B22(n/2, vector<int>(n/2));
    split(A, A11, A12, A21, A22);
    split(B, B11, B12, B21, B22);

    // Computing the 7 products
    vector<vector<int > > M1 = strassen(add(A11, A22), add(B11, B22));
    vector<vector<int > > M2 = strassen(add(A21, A22), B11);
    vector<vector<int > > M3 = strassen(A11, subtract(B12, B22));
    vector<vector<int > > M4 = strassen(A22, subtract(B21, B11));
    vector<vector<int > > M5 = strassen(add(A11, A12), B22);
    vector<vector<int > > M6 = strassen(subtract(A21, A11), add(B11, B12));
    vector<vector<int > > M7 = strassen(subtract(A12, A22), add(B21, B22));

    // Computing the quadrants of the product matrix
    vector<vector<int > > C11 = add(subtract(add(M1, M4), M5), M7);
    vector<vector<int > > C12 = add(M3, M5);
    vector<vector<int > > C21 = add(M2, M4);
    vector<vector<int > > C22 = add(subtract(add(M1, M3), M2), M6);

    // Joining the quadrants into the final matrix
    
    C = join(C11, C12, C21, C22);

    return C;
}

int main() {
    int n;
    cout << "Enter the size of the matrices: ";
    cin >> n;

    vector<vector<int > > A(n, vector<int>(n, 0));
    vector<vector<int > > B(n, vector<int>(n, 0));

    cout << "Enter the elements of matrix A: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter the elements of matrix B: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }	

    vector<vector<int > > C = strassen(A, B);

    cout << "Product of matrices A and B: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

