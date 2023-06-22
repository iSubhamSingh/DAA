#include <iostream>
using namespace std;

int main()
{
    int graph[100][100], weight[100], parent[100], n;
    bool visit[100];
    cout << "Enter the number of vertices in the graph: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Enter the weight of edge between " << i << " and " << j << ":  ";
            
            cin >> graph[i][j];
        }
        weight[i] = INT_MAX;
        visit[i] = false;
    }

    
    weight[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int i, min = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (visit[j] == false && weight[j] < min) {
                min = weight[j];
                i = j;
            }
        }
        visit[i] = true;
        for (int j = 0; j < n; j++) {
            if (graph[i][j] && visit[j] == false && graph[i][j] < weight[j]) {
                parent[j] = i;
                weight[j] = graph[i][j];
            }
        }
    }

   
    cout << "Edges of minimum spanning tree:" << endl;
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << endl;
    }
    int cost = 0;
    for (int i = 1; i < n; i++) {
        cost += graph[i][parent[i]];
    }
    cout << "Cost of minimum spanning tree: " << cost << endl;

    return 0;
}
