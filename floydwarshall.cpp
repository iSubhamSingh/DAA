#include <bits/stdc++.h>
using namespace std;

#define V 4
#define I 99999

void printSolution(int dist[][V]);
void floydWarshall(int dist[][V]) {
    int i, j, k;

    for (k = 0; k < V; k++) {
        printSolution(dist); // Print matrix after each node is added to the path
        cout << endl;

        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) &&
                    (dist[k][j] != I && dist[i][k] != I))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

void printSolution(int dist[][V]) {
    cout << "\n Shortest distance between every pair of vertices \n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == I)
                cout << "I" << " ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int graph[V][V];
    cout << "Enter the values , 'i' for infinity :\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string input;
            cin >> input;
            if (input == "i")
                graph[i][j] = i;
            else {
                stringstream ss(input);
                ss >> graph[i][j];
            }
        }
    }

    floydWarshall(graph);
    return 0;
}
