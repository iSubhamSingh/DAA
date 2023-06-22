#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 4; 


struct PuzzleState {
    int board[BOARD_SIZE][BOARD_SIZE]; 
    int cost;
    int depth;
    int blankRow;
    int blankCol;
    string path;

    // calculate distance
    int calCost() { 
        int sum = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                int value = board[i][j];
                if (value != 0) {
                    int targetRow = (value - 1) / BOARD_SIZE;
                    int targetCol = (value - 1) % BOARD_SIZE;
                    sum += abs(i - targetRow) + abs(j - targetCol); 
                }
            }
        }
        return sum;
    }
};

// comparison using priority queue.
struct ComparePuzzleState {
    bool operator()(const PuzzleState& a, const PuzzleState& b) {
        return (a.cost + a.depth) > (b.cost + b.depth);
    }
};

// check if a input state is goal state
bool isGoalState(const PuzzleState& state) {
    int value = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (state.board[i][j] != value && value != BOARD_SIZE * BOARD_SIZE) { //checking for index values and value goal state/cell
                return false;
            }
            value++;
        }
    }
    return true;
}

// check if a move is valid
bool isValidMove(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE); //checking for out of bounds
}

void makeMove(PuzzleState& state, int newRow, int newCol) {
    swap(state.board[state.blankRow][state.blankCol], state.board[newRow][newCol]); //swapping cells
    state.blankRow = newRow; 
    state.blankCol = newCol;
}

void printBoard(const PuzzleState& state) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << state.board[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// solve the puzzle using Branch and Bound technique
void solvePuzzle(const PuzzleState& initialState) {
    priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> pq;
    pq.push(initialState);

    int iteration = 0;
    while (!pq.empty() && iteration < 4) {
        PuzzleState currentState = pq.top(); 
        pq.pop(); 

        cout << "Iteration number: " << iteration << "\n";
        cout << "Current Cost: " << currentState.cost << endl;
        cout << "Current Path: " << currentState.path << endl;
        printBoard(currentState);

        if (isGoalState(currentState)) {
            cout << "Puzzle solved successfully \n";
            cout << "Minimum Cost: " << currentState.cost << endl;
            cout << "Minimum Path: " << currentState.path << endl;
            return;
        }

        int row = currentState.blankRow;
        int col = currentState.blankCol;

        // Move Up
        if (isValidMove(row - 1, col)) {
            PuzzleState newState = currentState;
            makeMove(newState, row - 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "U";
            pq.push(newState);
        }

        // Move Down
        if (isValidMove(row + 1, col)) {
            PuzzleState newState = currentState;
            makeMove(newState, row + 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "D";
            pq.push(newState);
        }

        // Move Left
        if (isValidMove(row, col - 1)) {
            PuzzleState newState = currentState;
            makeMove(newState, row, col - 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "L";
            pq.push(newState);
        }

        // Move Right
        if (isValidMove(row, col + 1)) {
            PuzzleState newState = currentState;
            makeMove(newState, row, col + 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "R";
            pq.push(newState);
        }

        iteration++;
    }

    cout << "Can't find solution within the iteration'\n";
}

int main() {
    PuzzleState initialState;
    cout << "Enter the start state of the puzzle . Input 0 for blank \n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cin >> initialState.board[i][j];
            if (initialState.board[i][j] == 0) { 
                initialState.blankRow = i;
                initialState.blankCol = j;
            }
        }
    }

    initialState.cost = initialState.calCost();
    initialState.depth = 0;
    initialState.path = "";

    solvePuzzle(initialState);

    return 0;
}

