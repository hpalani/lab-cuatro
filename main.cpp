/*
 NAME: Harish Palani
 CRN: 11467
 ASSIGNMENT: Lab 4
 SOURCES: stackoverflow.com, geeksforgeeks.org
 */

#include <iostream>
#include <sstream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;


#define edge pair<int,int>

// Global variables
int V = 0, E = 0;

// Functions
int minimumKeyValue(int key[], bool mst[]);

// Add-ons for Kruskal's implementation
class Graph {
    
    private:
        vector<pair<int, edge>> G; // graph
        vector<pair<int, edge>> T; // mst
        int *parent;
        int V; // number of vertices/nodes in graph
    
    public:
        Graph(int V);
        void addEdge(int u, int v, int w);
        int findSet(int i);
        void unionSet(int u, int v);
        void kruskal();
        void print();
        
};

Graph::Graph(int V) {
    parent = new int[V];
    for (int i = 0; i < V; i++) { parent[i] = i; }
    G.clear();
    T.clear();
}

void Graph::addEdge(int u, int v, int w) { G.push_back(make_pair(w, edge(u, v))); }
int Graph::findSet(int i) {
    if (i == parent[i]) { return i; }
    else { return findSet(parent[i]); }
}
void Graph::unionSet(int u, int v) { parent[u] = parent[v]; }

// Core implementation of Kruskal's algorithm
void Graph::kruskal() {
    int i, uSet, vSet;
    sort(G.begin(), G.end());
    for (i = 0; i < G.size(); i++) {
        uSet = findSet(G[i].second.first);
        vSet = findSet(G[i].second.second);
        if (uSet != vSet) {
            T.push_back(G[i]);
            unionSet(uSet, vSet);
        }
    }
}

int main() {    
    string row, temp;
    int totalWeight = 0;
    
    // Define WAM size with number of vertices.
    cout << "How many vertices will your weighted adjacency matrix have?: ";
    cin >> V;
    int wamInput[V][V];
    int wamOutput[V][V];
    Graph g(V);
    
    // Initialize wamOutput to zero.
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            wamOutput[i][j] = 0;
        }    
    }
    
    // Accept input WAM contents.
    cout << endl;
    cout << "Enter WAM below, with all entries separated by spaces." << endl;
    
    int numEntries = 0;
    for (int i = 0; i < V; i++) {
        
        if (i < 9) { cout << " Row #"; }
        else { cout << "Row #"; }
        
        cout << i + 1 << ": ";
        if (i == 0) { cin.ignore(); }
        getline(cin, row);
        temp.assign(row);
        
        stringstream rowstream(row);
        int n = 0, counter = 0;
                
        while (rowstream >> n && counter < V) {
            wamInput[i][counter] = n;
            counter++;
            numEntries++;
        }
    }
    
    // Load WAM contents into Kruskal graph.
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g.addEdge(i, j, wamInput[i][j]);
        }
    }
    
    // Print out input WAM contents.
    cout << endl;
    cout << "The input weighted adjacency matrix is: " << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << wamInput[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    /* KRUSKAL'S ALGORITHM (Extra credit) */
    // Compute output WAM & corresponding weight using Kruskal's algorithm
    g.kruskal();
    
    /* PRIM'S ALGORITHM */
    // Compute output WAM & corresponding weight using Prim's algorithm.
    int parent[V]; // Store constructed MST.
    int key[V];    // Consolidate system keys.
    bool mst[V];   // Track vertices not yet included in MST.
 
    // Initialize keys.
    for (int i = 0; i < V; i++) { key[i] = INT_MAX, mst[i] = false; }
    
    // Include first vertex in MST -- it should be the root.
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < V - 1; count++) {
        int u = minimumKeyValue(key, mst);
        mst[u] = true;
        
        for (int v = 0; v < V; v++) {
          if (wamInput[u][v] && mst[v] == false && wamInput[u][v] <  key[v]) {
              parent[v]  = u;
              key[v] = wamInput[u][v];
          }
        }
     }
    
     // Construct output WAMs and print out results.
    for (int i = 1; i < V; i++) {
        int x = parent[i], y = i, weight = wamInput[i][parent[i]];
        wamOutput[x][y] = weight;
        wamOutput[y][x] = weight;
        totalWeight = totalWeight + weight;
    }
    
    // Print all results: Kruskal's first, then Prim's
    cout << "The output from Kruskal's algorithm is: " << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << wamOutput[i][j] << "\t";
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "The total weight of the graph is ";
    cout << totalWeight << "." << endl;
    cout << endl;
    
    cout << "The output from Prim's algorithm is: " << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << wamOutput[i][j] << "\t";
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "The total weight of the graph is ";
    cout << totalWeight << "." << endl;
}


/* Finds vertex with the mininum key value of vertices not yet in MST */
int minimumKeyValue(int key[], bool mst[]) {
   // Initialize variables.
   int min = INT_MAX, minimumIndex;
   
   // Determine minimum vertex.
   for (int v = 0; v < V; v++) {
     if (mst[v] == false && key[v] < min) {
         min = key[v], minimumIndex = v;
     }
   }
 
   return minimumIndex;
}