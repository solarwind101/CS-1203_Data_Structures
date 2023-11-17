/* This code implements Dijkstra’s algorithm for finding the shortest path in a graph. 
It uses an adjacency matrix to represent the graph, and a boolean array sptSet[] 
to keep track of vertices included in the shortest path tree.
 The dist[] array is used to hold the shortest distance from the source to each vertex, 
and the parent[] array is used to store the shortest path tree. */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 9  // Number of vertices in the graph

// Function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the shortest path from the source to j using the parent array
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}

// Function to print the constructed distance array and shortest paths
void printSolution(int dist[], int parent[]) {
    printf("Vertex \t\t Distance from Source\tPath\n");
    for (int i = 1; i < V; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", 0, i, dist[i], 0);
        printPath(parent, i);
    }
}

// Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src) {
    int dist[V];  // The output array. dist[i] will hold the shortest distance from src to i
    bool sptSet[V];  // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
    int parent[V];  // This array is used to store the shortest path tree

    for (int i = 0; i < V; i++) {
        parent[0] = -1;  // Parent of source is always -1
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;  // Distance of source vertex from itself is always 0

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);  // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
        sptSet[u] = true;  // Mark the picked vertex as processed

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printSolution(dist, parent);  // print the constructed distance array and shortest paths
}

int main() {
    // Graph
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    dijkstra(graph, 0);  // Function call

    return 0;
}
