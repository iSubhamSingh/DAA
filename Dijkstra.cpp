#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX; // Infinity

// Graph representation using adjacency list
typedef pair<int, int> pii; 
typedef vector<vector<pii> > Graph;


void dijkstra(const Graph& graph, int source) {
    int n = graph.size();

    
    vector<int> distance(n, INF);
    distance[source] = 0;

    // Priority queue to store vertices based on minimum distance
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        
        if (dist > distance[u])
            continue;

        
        for (int i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i].first;
            int weight = graph[u][i].second;

          
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push(make_pair(distance[v], v));
            }
        }
    }


    cout << "Shortest distances from source " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": ";
        if (distance[i] == INF)
            cout << "Infinity\n";
        else
            cout << distance[i] << "\n";
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    // Create a graph with n vertices
    Graph graph(n);

    cout << "Enter the edges (source destination weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].push_back(make_pair(v, weight));
        graph[v].push_back(make_pair(u, weight));
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    dijkstra(graph, source);

    return 0;
}

