/*
 NAME: Harish Palani
 CRN: 11467
 ASSIGNMENT: Lab 4
 SOURCES: stackoverflow.com, geeksforgeeks.org
 */

#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <climits>

using namespace std;

// Global variables
int V = 0, E = 0;

// Functions
int minimumKeyValue(int key[], bool mst[]);

int main() {    
    string row, temp;
    int totalWeight = 0;
    
    // Define WAM size with number of vertices.
    cout << "How many vertices will your weighted adjacency matrix have?: ";
    cin >> V;
    int wamInput[V][V];
    int primOutput[V][V];
    
    // Initialize primOutput to zero.
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            primOutput[i][j] = 0;
        }    
    }
    
    // Accept input WAM contents.
    cout << endl;
    cout << "Enter WAM below, with all entries separated by spaces." << endl;
    for (int i = 0; i < V; i++) {
        
        if (i < 9) { cout << " Row #"; }
        else { cout << "Row #"; }
        
        cout << i + 1 << ": ";
        if (i == 0) { cin.ignore(); }
        getline(cin, row);
        temp.assign(row);
        
        stringstream rowstream(row);
        int n, counter = 0;
                
        while (rowstream >> n && counter < V) {
            wamInput[i][counter] = n;
            counter++;
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
    
    /* KRUSKAL'S ALGORITHM */
    
    // Compute output WAM & corresponding weight using Kruskal's algorithm
    cout << "The output from Kruskal's algorithm is: " << endl;
    
    
    
    cout << endl;
    
    // Print weight of output WAM.
    cout << endl;
    cout << "The total weight of the graph is ";
    cout << totalWeight << "." << endl;
    
    cout << endl;
    
    /* PRIM'S ALGORITHM */
    
    // Compute output WAM & corresponding weight using Prim's algorithm.
    cout << "The output from Prim's algorithm is: " << endl;
    
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
    
     // Construct output WAM and print out results.
    for (int i = 1; i < V; i++) {
        int x = parent[i], y = i, weight = wamInput[i][parent[i]];
        primOutput[x][y] = weight;
        primOutput[y][x] = weight;
        totalWeight = totalWeight + weight;
    }
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << primOutput[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Print weight of output WAM.
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