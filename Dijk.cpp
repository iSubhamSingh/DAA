#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); 


struct Edge {
    int destination;  
    int weight;       

    Edge(int destination, int weight) : destination(destination), weight(weight) {}
};


struct Node {
    int id;           
    int distance;     

    Node(int id, int distance) : id(id), distance(distance) {}

    
    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

// Function to perform Dijkstra's algorithm on a graph
void dijkstra(const vector<vector<Edge> >& graph, int source) {
    int numNodes = graph.size();

    
    vector<int> distance(numNodes, INF);
    
    vector<int> previous(numNodes, -1);
    
    priority_queue<Node> pq;


    distance[source] = 0;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        // Get the node with the minimum distance from the priority queue
        Node currentNode = pq.top();
        pq.pop();

        int currentNodeID = currentNode.id;
        int currentDistance = currentNode.distance;

        // Skip the node if it has already been visited
        if (currentDistance > distance[currentNodeID]) {
            continue;
        }

        // Explore the neighbors of the current node
        for (int i = 0; i < graph[currentNodeID].size(); ++i) {
            Edge edge = graph[currentNodeID][i];
            int neighborID = edge.destination;
            int newDistance = currentDistance + edge.weight;

            // Update the distance and previous node if a shorter path is found
            if (newDistance < distance[neighborID]) {
                distance[neighborID] = newDistance;
                previous[neighborID] = currentNodeID;
                pq.push(Node(neighborID, newDistance));
            }
        }
    }

    
    for (int i = 0; i < numNodes; ++i) {
        cout << "Shortest path from node " << source << " to node " << i << ": ";

        if (distance[i] == INF) {
            cout << "No path" << endl;
        } else {
            cout << distance[i] << " (";
            int node = i;
            while (node != -1) {
                cout << node;
                node = previous[node];
                if (node != -1) {
                    cout << " <- ";
                }
            }
            cout << ")" << endl;
        }
    }
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes in the graph: ";
    cin >> numNodes;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    
    vector<vector<Edge> > graph(numNodes);

    
    cout << "Enter the edges and their weights:" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph[source].push_back(Edge(destination, weight));
    }

    int sourceNode;
    cout << "Enter the source node: ";
    cin >> sourceNode;

    // Perform Dijkstra's algorithm on the graph
    dijkstra(graph, sourceNode);

    return 0;
}

