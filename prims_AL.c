#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// Structure for a node in adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};
// Structure for adjacency list
struct AdjList {
    struct Node* head;
};
// Structure for graph
struct Graph {
    int numVertices;
    struct AdjList* array;
    int** matrix; // Adjacency matrix
};
// Function to create a new node
struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
// Function to create a graph with 'numVertices' vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));
    graph->matrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        graph->array[i].head = NULL;
        graph->matrix[i] = (int*)calloc(numVertices, sizeof(int));
    }
    return graph;
}
// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add an edge from dest to src as well (assuming undirected graph)
    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;

    // Update adjacency matrix
    graph->matrix[src][dest] = weight;
    graph->matrix[dest][src] = weight;
}

// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[], int numVertices) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < numVertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}
// Function to print the minimum spanning tree
void printMST(int parent[], int** graph, int numVertices) {
    printf("Edge   Weight\n");
    for (int i = 1; i < numVertices; i++)
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}
// Function to implement Prim's algorithm to find minimum spanning tree
void primMST(struct Graph* graph) {
    int numVertices = graph->numVertices;
    int* parent = (int*)malloc(numVertices * sizeof(int));
    int* key = (int*)malloc(numVertices * sizeof(int));
    int* mstSet = (int*)malloc(numVertices * sizeof(int));
    // Initialize all keys as INFINITE and mstSet[] as 0
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    // Initialize first vertex as root
    key[0] = 0;
    parent[0] = -1;
    // The MST will have numVertices - 1 edges
    for (int count = 0; count < numVertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, numVertices);
        mstSet[u] = 1;
        // Update key value and parent index of the adjacent vertices of the picked vertex
        struct Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (mstSet[v] == 0 && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
            temp = temp->next;
        }
    }
    // Print the minimum spanning tree
    printMST(parent, graph->matrix, numVertices);
}
int main() {
    int numVertices, numEdges, src, dest, weight;
    printf("Enter number of vertices in the graph: ");
    scanf("%d", &numVertices);
    struct Graph* graph = createGraph(numVertices);
    printf("Enter number of edges in the graph: ");
    scanf("%d", &numEdges);
    for (int i = 0; i < numEdges; ++i) {
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }
    // Print the minimum spanning tree using Prim's algorithm
    printf("Minimum Spanning Tree using Prim's Algorithm:\n");
    primMST(graph);
    return 0;
}
