#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define INF INT_MAX

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;  // adj[u] = {v, weight}

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // Undirected graph
    }

    void primMST() {
        vector<bool> inMST(V, false);       // track visited nodes
        vector<int> key(V, INF);            // minimum edge weight to reach node
        vector<int> parent(V, -1);          // store MST structure
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        key[0] = 0;
        pq.push({0, 0});  // {key, vertex}

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        int totalCost = 0;
        cout << "Edges in the Minimum Spanning Tree:\n";
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " (Cost: " << key[i] << ")\n";
            totalCost += key[i];
        }
        cout << "Total cost of leasing phone lines: " << totalCost << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of offices (vertices): ";
    cin >> V;
    cout << "Enter number of available phone lines (edges): ";
    cin >> E;

    Graph g(V);
    cout << "Enter phone line data (office1 office2 cost):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.primMST();

    return 0;
}
