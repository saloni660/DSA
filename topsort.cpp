#include <bits/stdc++.h>
using namespace std;

// DFS function for Topological Sort
void dfs(int node, vector<bool>& visited, stack<int>& topstack, vector<vector<int>>& adj) {
    visited[node] = true;
    for (int n : adj[node]) {
        if (!visited[n]) {
            dfs(n, visited, topstack, adj);
        }
    }
    topstack.push(node);
}

// BFS function
void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int v, e;
    cout << "Graph Traversals: Topological Sort (DFS) and BFS\n";
    cout << "--------------------------------------------------\n";

    cout << "Enter the number of vertices: ";
    cin >> v;

    cout << "Enter the number of directed edges: ";
    cin >> e;

    vector<vector<int>> adj(v);

    cout << "Enter " << e << " edges in the format (from to):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // --------- Topological Sort (DFS) ---------
    vector<bool> visited(v, false);
    stack<int> topstack;

    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            dfs(i, visited, topstack, adj);
        }
    }

    cout << "\nTopological Sort (DFS Order): ";
    while (!topstack.empty()) {
        cout << topstack.top() << " ";
        topstack.pop();
    }
    cout << endl;

    // --------- BFS Traversal ---------
    visited.assign(v, false); // reset visited for BFS

    cout << "\nBFS Traversal starting from each unvisited vertex:\n";
    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            bfs(i, adj, visited);
        }
    }
    cout << endl;

    return 0;
}
