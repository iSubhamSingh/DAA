#include <iostream>
#include <vector>

using namespace std;

vector<vector<int > > constructTransitionMatrix(const string& pattern, const string& alphabet) {
    int m = pattern.length();
    int n = alphabet.length();
    vector<vector<int > > transitionMatrix(m + 1, vector<int>(n));

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            string prefix = pattern.substr(0, i) + alphabet[j];
            int k = min(m + 1, i + 2);
            while (k > 0) {
                --k;
                if (prefix.substr(i - k + 1) == pattern.substr(0, k)) {
                    transitionMatrix[i][j] = k;
                    break;
                }
            }
        }
    }

    return transitionMatrix;
}

bool stringMatching(const string& text, const string& pattern, const vector<vector<int > >& transitionMatrix) {
    int m = pattern.length();
    int currentState = 0;
    
    for (int i = 0; i < text.length(); ++i) {
        int j;
        for (j = 0; j < transitionMatrix[currentState].size(); ++j) {
            if (text[i] == pattern[currentState]) {
                currentState = transitionMatrix[currentState][j];
                break;
            }
        }
        if (j == transitionMatrix[currentState].size()) {
            currentState = 0;
        }

        if (currentState == m) {
            return true;
        }
    }

    return false;
}

void printTransitionMatrix(const vector<vector<int > >& transitionMatrix, const string& alphabet) {
    cout << "Transition Matrix:\n";
    cout << "  ";
    for (int i = 0; i < alphabet.length(); ++i) {
        cout << alphabet[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < transitionMatrix.size(); ++i) {
        cout << i << " ";
        for (int j = 0; j < transitionMatrix[i].size(); ++j) {
            cout << transitionMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    string pattern, text, alphabet;
    cout << "Enter the pattern: ";
    cin >> pattern;
    cout << "Enter the text: ";
    cin >> text;
    cout << "Enter the alphabet: ";
    cin >> alphabet;

    vector<vector<int > > transitionMatrix = constructTransitionMatrix(pattern, alphabet);

    printTransitionMatrix(transitionMatrix, alphabet);

    bool isMatch = stringMatching(text, pattern, transitionMatrix);

    if (isMatch) {
        cout << "Pattern found in the text.\n";
    } else {
        cout << "Pattern not found in the text.\n";
    }

    return 0;
}

