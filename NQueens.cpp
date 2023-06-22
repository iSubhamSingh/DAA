#include <iostream>
#include <vector>

using namespace std;

// function to check if a queen can be placed in the current position
bool isSafe(vector<vector<int > >& board, int row, int col, int n) {
    // check the row
    for (int i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }
    // check the upper diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false; 
        }
    }
    // check the lower diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }
    return true;
}

// recursive function to solve the n-queens problem
void solveNQueens(vector<vector<int > >& board, int col, int n, int& count) {
    // base case: all queens are placed
    if (col == n) {
        count++;
        // print the board
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    // try to place a queen in each row of the current column
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            board[i][col] = 1;
            solveNQueens(board, col + 1, n, count);
            board[i][col] = 0;
        }
    }
}

// function to solve the n-queens problem
void nQueens(int n) {
    vector<vector<int > > board(n, vector<int>(n, 0));
    int count = 0;
    solveNQueens(board, 0, n, count);
    cout << "Number of solutions: " << count << endl;
}

// main function
int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    nQueens(n);
    return 0;
}

