/* Yes, Dijkstra’s algorithm can be used in directed graphs. In the context of a directed graph, Dijkstra’s algorithm takes into account the direction of the edges 
when visiting the neighbors of a vertex1. This means that it only considers edges that point away from 
the current vertex. If there is an edge from vertex A to vertex B, but not from B to A, 
then the algorithm will consider A as a neighbor of B, but not vice versa1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define infi 1000000000
#define V 4

typedef struct Node {
    int vertexNumber;
    int children[V];
    int weights[V];
    int childrenCount;
} Node;

Node* createNode(int vertexNumber) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->vertexNumber = vertexNumber;
    node->childrenCount = 0;
    return node;
}

void add_child(Node* node, int vNumber, int length) {
    node->children[node->childrenCount] = vNumber;
    node->weights[node->childrenCount] = length;
    node->childrenCount++;
}

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j]==-1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}

void dijkstra(Node* graph[], int src) {
    int dist[V];
    int sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        parent[0] = -1;
        dist[i] = infi;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V-1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < graph[u]->childrenCount; v++) {
            int vertex = graph[u]->children[v];
            int weight = graph[u]->weights[v];
            if (!sptSet[vertex] && dist[u] != INT_MAX && dist[u]+weight < dist[vertex]) {
                parent[vertex] = u;
                dist[vertex] = dist[u] + weight;
            }
        }
    }

    printf("Vertex\t\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\t\tPath ", i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}

int main() {
    Node* graph[V];
    for (int i = 0; i < V; i++) {
        graph[i] = createNode(i);
    }

    add_child(graph[0], 1, 1);
    add_child(graph[0], 2, 4);
    add_child(graph[1], 2, 2);
    add_child(graph[1], 3, 6);
    add_child(graph[2], 3, 3);

    dijkstra(graph, 0);

    return 0;
}
