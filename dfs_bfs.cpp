#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // Undirected graph
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Unified DFS that works for both traversal and component counting
    void DFS(int start, vector<bool>& visited, bool print = false) {
        stack<int> s;
        s.push(start);

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                if (print) cout << v << " ";
            }

            for (int i = V - 1; i >= 0; i--) {
                if (adjMatrix[v][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }

    void runDFS() {
        vector<bool> visited(V, false);
        cout << "DFS Traversal (Iterative): ";
        DFS(0, visited, true); // only prints when 'print' flag is true
        cout << endl;
    }

    void BFS() {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[0] = true;
        q.push(0);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int i = 0; i < V; i++) {
                if (adjMatrix[v][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    int countConnectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i, visited, false); // no print while counting
                count++;
            }
        }
        return count;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter " << E << " edges (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.displayMatrix();
    g.runDFS();
    g.BFS();

    int components = g.countConnectedComponents();
    if (components == 1)
        cout << "\nThe graph is connected.\n";
    else
        cout << "\nThe graph is not connected. It has " << components << " connected components.\n";

    return 0;
}
