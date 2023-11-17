/*
*The time complexity of Dijkstra's algorithm can be improved from O(V^2) 
*to O((V + E) * log(V)) by using a priority queue data structure. 
*The priority queue efficiently keeps track of the vertex with the
*shortest tentative distance from the source, allowing for
*faster extraction of the minimum distance vertex and updating of 
*adjacent vertices.

*This improvement is particularly significant in sparse graphs where the 
*number of edges (E) is much less than the number of vertices (V). 
*The use of a priority queue, implemented with data structures like 
*a binary heap or Fibonacci heap, reduces the time complexity 
*of extracting the minimum distance vertex from O(V) to O(log(V)), 
*leading to an overall improvement in the algorithm's performance
*/
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define V 9

struct MinHeapNode {
    int v;
    int dist;
};

struct MinHeap {
    int size;
    int capacity;
    struct MinHeapNode** array;
};

// Function declarations
struct MinHeapNode* newMinHeapNode(int v, int dist);
struct MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
bool isEmpty(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void decreaseKey(struct MinHeap* minHeap, int v, int dist, int* size);
void printSolution(int dist[], int n);

// Forward declaration for dijkstra function
void dijkstra(int graph[V][V], int src);

// Function implementations

// Create a new MinHeapNode
struct MinHeapNode* newMinHeapNode(int v, int dist) {
    struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    newNode->v = v;
    newNode->dist = dist;
    return newNode;
}

// Create a new MinHeap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Swap two MinHeapNodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify a subtree rooted with the given index
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[idx], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

// Check if the heap is empty
bool isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Extract the MinHeapNode with the minimum distance
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Decrease the distance value of a given vertex
void decreaseKey(struct MinHeap* minHeap, int v, int dist, int* size) {
    int i;
    for (i = 0; i < *size; ++i) {
        if (minHeap->array[i]->v == v)
            break;
    }

    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Print the solution (final distances)
void printSolution(int dist[], int n) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

// Dijkstra's algorithm using a priority queue
void dijkstra(int graph[V][V], int src) {
    int dist[V];
    struct MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->size++;
    }

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src], &minHeap->size);

    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                decreaseKey(minHeap, v, dist[v], &minHeap->size);
            }
        }
    }

    printSolution(dist, V);
}

// Driver program
int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(graph, 0);

    return 0;
}
