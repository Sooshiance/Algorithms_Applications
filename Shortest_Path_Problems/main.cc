#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define a structure to represent a graph
class Graph {
public:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list (node, weight)

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w)); // For undirected graph
    }

    void dijkstra(int src) {
        // Min-heap priority queue
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Distance vector initialized to infinity
        vector<int> dist(V, numeric_limits<int>::max());
        dist[src] = 0;
        pq.push(make_pair(0, src)); // (distance, vertex)

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Traverse adjacent vertices
            for (auto &neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        // Print the shortest distances from source
        cout << "Vertex Distance from Source (" << src << "):" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << " : " << dist[i] << endl;
        }
    }
};

int main() {
    Graph g(9); // Create a graph with 9 vertices

    // Add edges (u, v, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.dijkstra(0); // Calculate shortest paths from vertex 0

    return 0;
}