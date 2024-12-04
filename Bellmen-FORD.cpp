#include <iostream>
#include <vector>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8);
    dist[src] = 0;
    for (int i = 0; i < V; i++) {
        for (vector<int> edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                if (i == V - 1)
                    return { -1 };
                dist[v] = dist[u] + wt;
            }
        }
    }
    return dist;
}

int main() {
    int V, E, src;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    vector<vector<int>> edges;
    cout << "Enter each edge as: <from> <to> <weight>\n";
    for (int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({ u, v, wt });
    }
    cout << "Enter the source vertex: ";
    cin >> src;
    vector<int> ans = bellmanFord(V, edges, src);
    if (ans[0] == -1) {
        cout << "A negative weight cycle is detected in the graph.\n";
    } else {
        cout << "\nShortest distances from source vertex " << src << ":\n";
        for (int i = 0; i < V; i++) {
            if (ans[i] == 1e8)
                cout << "Vertex " << i << ": No path from source\n";
            else
                cout << "Vertex " << i << ": " << ans[i] << "\n";
        }
    }
    return 0;
}
