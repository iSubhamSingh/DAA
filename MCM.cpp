#include <iostream>
#include <vector>
#include <climits>  
#include <cstring> 

using namespace std;

void printMatrixChainOrder(vector<vector<int> >& s, int i, int j) {
    if (i == j) {
        cout << "A" << i + 1;
        return;
    }

    cout << "(";
    printMatrixChainOrder(s, i, s[i][j]);
    cout << " x ";
    printMatrixChainOrder(s, s[i][j] + 1, j);
    cout << ")";
}

void matrix_chain_multiplication(vector<int> p) {
    int n = p.size() - 1;
    vector<vector<int> > m(n, vector<int>(n, 0));  
    vector<vector<int> > s(n, vector<int>(n, 0)); 
    
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;  
            
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
                
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    
    // Print the minimum number of multiplications required
    cout << "Minimum number of multiplications required: " << m[0][n-1] << endl;
    
    // Print the intermediate matrices
    cout << "Intermediate Matrices:\n";
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            cout << "Matrix A" << i + 1 << " to A" << j + 1 << ":\n";
            for (int k = i; k < j; k++) {
                cout << "A" << i + 1 << " x A" << k + 2 << " x A" << j + 2 << endl;
            }
            cout << endl;
        }
    }
    
    // Print the matrix chain multiplication steps
    cout << "Matrix Chain Multiplication Steps:\n";
    printMatrixChainOrder(s, 0, n - 1);
    cout << endl;
}

int main() {
    vector<int> p;
    int n;
    cout << "Enter the size of the vector: ";
    cin >> n;
    cout << "Enter the elements of the vector: ";
    for (int i = 0; i < n; i++) {
        int element;
        cin >> element;
        p.push_back(element);
    }
    matrix_chain_multiplication(p);
    return 0;
}


