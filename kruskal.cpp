#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class DSU {
    int* parent;
    int* rank;

public:
    
    DSU(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = -1; // Initially, every node is its own parent
            rank[i] = 1;    // Initial rank is 1
        }
    }

    // Find the root of a set with path compression
    int find(int i) {
        if (parent[i] == -1) {
            return i; // If no parent, the node is its own root
        }
        return parent[i] = find(parent[i]); // Path compression
    }

    // Union of two sets by rank
    void unite(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            // Attach the smaller tree under the larger tree
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            } else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            } else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }

    // Destructor: Free dynamically allocated memory
    ~DSU() {
        delete[] parent;
        delete[] rank;
    }
};

// Graph class to represent the graph and implement Kruskal's Algorithm
class Graph {
    vector<vector<int>> edgelist; // Stores edges in the format {weight, vertex1, vertex2}
    int V;                        // Number of vertices

public:
    // Constructor: Initialize the graph with V vertices
    Graph(int V) {
        this->V = V;
    }

    // Add an edge to the edge list
    void addEdge(int x, int y, int w) {
        edgelist.push_back({w, x, y});
    }

    // Kruskal's algorithm to find the Minimum Spanning Tree (MST)
    void kruskals_mst() {
        // Sort edges by weight
        sort(edgelist.begin(), edgelist.end());

        // Create a DSU object
        DSU s(V);

        int mstWeight = 0; // Total weight of the MST
        cout << "Edges in the constructed MST:" << endl;

        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            // Check if the edge forms a cycle
            if (s.find(x) != s.find(y)) {
                // Include the edge in the MST
                s.unite(x, y);
                mstWeight += w;
                cout << x << " -- " << y << " == " << w << endl;
            }
        }

        cout << "Minimum Cost Spanning Tree: " << mstWeight << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter the edges (format: vertex1 vertex2 weight):" << endl;
    for (int i = 0; i < E; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        g.addEdge(x, y, w);
    }

    g.kruskals_mst();
    return 0;
}
