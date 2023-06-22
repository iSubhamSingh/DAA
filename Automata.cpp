#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<vector<int>> constructTransitionMatrix(const string& pattern, const unordered_set<char>& alphabet) {
    int m = pattern.length();
    vector<vector<int>> transitionMatrix(m + 1, vector<int>(alphabet.size()));

    for (int i = 0; i <= m; ++i) {
        for (char c : alphabet) {
            string prefix = pattern.substr(0, i) + c;
            int k = min(m + 1, i + 2);
            while (k > 0) {
                --k;
                if (prefix.substr(i - k + 1) == pattern.substr(0, k)) {
                    transitionMatrix[i][c] = k;
                    break;
                }
            }
        }
    }

    return transitionMatrix;
}

bool stringMatching(const string& text, const string& pattern, const vector<vector<int>>& transitionMatrix) {
    int m = pattern.length();
    int currentState = 0;
    bool isMatch = false;

    cout << "Transition Steps:\n";
    cout << "-----------------\n";
    cout << "State\tInput\tNext State\n";
    cout << "-----------------\n";

    for (char c : text) {
        int nextState = transitionMatrix[currentState][c];
        cout << currentState << "\t" << c << "\t" << nextState << endl;
        currentState = nextState;

        if (currentState == m) {
            isMatch = true;
            break;
        }
    }

    cout << "-----------------\n";

    return isMatch;
}

void printTransitionMatrix(const vector<vector<int>>& transitionMatrix, const unordered_set<char>& alphabet) {
    cout << "Transition Matrix:\n";
    cout << "  ";
    for (char c : alphabet) {
        cout << c << " ";
    }
    cout << endl;

    for (int i = 0; i < transitionMatrix.size(); ++i) {
        cout << i << " ";
        for (char c : alphabet) {
            cout << transitionMatrix[i][c] << " ";
        }
        cout << endl;
    }
}

int main() {
    string pattern, text;
    cout << "Enter the pattern: ";
    cin >> pattern;
    cout << "Enter the text: ";
    cin >> text;

    unordered_set<char> alphabet;
    for (char c : pattern) {
        alphabet.insert(c);
    }

    vector<vector<int>> transitionMatrix = constructTransitionMatrix(pattern, alphabet);

    printTransitionMatrix(transitionMatrix, alphabet);

    bool isMatch = stringMatching(text, pattern, transitionMatrix);

    if (isMatch) {
        cout << "Pattern found in the text.\n";
    } else {
        cout << "Pattern not found in the text.\n";
    }

    return 0;
}

