#include <stdio.h>

#define V 4
#define INF 99999

/* A utility function to print solution */
void printSolution(int dist[][V]) {
    printf(
        "The following matrix shows the shortest distances"
        " between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int dist[][V]) {
    int i, j, k;
    int parent[V][V]; // Parent information matrix

    // Initialize parent matrix
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            parent[i][j] = i; // Initialize with direct edge
        }
    }

    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of
                // dist[i][j] and parent[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j]; // Update parent information
                }
            }
        }
    }

    // Check for negative cycles
    for (int k = 0; k < V; k++) {
        if (dist[k][k] < 0) {
            // Handle negative cycle (e.g., report an error)
            printf("Negative cycle detected at vertex %d\n", k);
            return;
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);

    // Print parent information matrix (optional)
    // printf("\nParent Information Matrix:\n");
    // printSolution(parent);
}

// driver's code
int main() {
    int graph[V][V] = {{0, 5, INF, 10},
                       {INF, 0, 3, INF},
                       {INF, INF, 0, 1},
                       {INF, INF, INF, 0}};

    // Function call
    floydWarshall(graph);
    return 0;
}
