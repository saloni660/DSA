#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
    
    // Sorting edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by rank
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int main() {
    int V, E;
    cout << "Enter number of offices (vertices): ";
    cin >> V;
    cout << "Enter number of available phone lines (edges): ";
    cin >> E;

    vector<Edge> edges;
    cout << "Enter phone line data (office1 office2 cost):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // Sort edges by cost
    sort(edges.begin(), edges.end());

    DSU dsu(V);
    int totalCost = 0;

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (Edge e : edges) {
        if (dsu.unite(e.u, e.v)) {
            cout << e.u << " - " << e.v << " (Cost: " << e.weight << ")\n";
            totalCost += e.weight;
        }
    }

    cout << "Total cost of leasing phone lines: " << totalCost << endl;

    return 0;
}
