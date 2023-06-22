#include <iostream>
#include <vector>
#include <climits>  
#include <cstring> 

using namespace std;

void matrix_chain_multiplication(vector<int> p) {
    int n = p.size() - 1;
    vector<vector< int > > m(n, vector<int>(n, 0));  
    vector<vector<int > > s(n, vector<int>(n, 0)); 
    
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
    
    // Print the 2D matrix containing intermediate results
    cout << "2D matrix containing intermediate results:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << "0\t";
            } else if (j < i) {
                cout << "-\t";
            } else {
                cout << m[i][j] << "\t";
            }
        }
        cout << endl;
    }
    
    // Print the matrix of dimensions
    cout << "Matrix of dimensions:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << "A" << i+1 << "\t";
            } else if (j < i) {
                cout << "-\t";
            } else {
                cout << "A" << i+1 << "x" << "A" << j+1 << "\t";
            }
        }
        cout << endl;
    }
    
    // Print the split positions
    cout << "Split positions:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << "-\t";
            } else if (j < i) {
                cout << "-\t";
            } else {
                cout << "K" << s[i][j] + 1 << "\t";
            }
        }
        cout << endl;
    }
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


