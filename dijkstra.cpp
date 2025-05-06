#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> adj;
    public:
    Graph(int V){
        this->V=V;
        adj.resize(V);
    }

    void add(int u,int v,int w){
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    void dijktra(int src){
        vector<int> dist(V,INF);
        vector<int> parent(V,-1);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,src});
        dist[src]=0;

        while(!pq.empty()){
            int u=pq.top().second;
            pq.pop();
            for(auto n:adj[u]){
                int v=n.first;
                int weight=n.second;
                if(dist[u]+weight<dist[v]){
                    dist[v]=dist[u]+weight;
                    parent[v]=u;
                    pq.push({dist[v],v});
                }
            }
        }
        cout << "\nShortest distances from vertex 0:\n";
        for (int i = 0; i < V; i++) {
            cout << "To vertex " << i << " = ";
            if (dist[i] == INF) {
                cout << "Unreachable\n";
            } else {
                cout << dist[i] << " via path: ";
                printPath(parent, i);
                cout << endl;
            }
        }
    }

    void printPath(vector<int>& parent, int vertex) {
        if (vertex == -1) return;
        printPath(parent, parent[vertex]);
        cout << vertex << " ";
    }
};

int main() {
    int V, E;
    cout << "Enter number of cities (vertices): ";
    cin >> V;
    cout << "Enter number of routes (edges): ";
    cin >> E;

    Graph g(V);
    cout << "Enter routes (city1 city2 distance):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add(u, v, w);
    }

    g.dijktra(0); // Always start from vertex 0

    return 0;
}
    
