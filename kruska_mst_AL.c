
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};
// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};
// Structure to represent the adjacency list
struct AdjList {
    struct Node* head;
};
// Structure to represent the graph
struct Graph {
    int numVertices;
    struct AdjList* array;
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
    for (int i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;
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
}
// Function to find the subset of an element 'i'
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}
// Function to do union of two subsets
void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}
// Comparator function used for sorting edges by weight
int compare(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}
// Function to implement Kruskal's algorithm to find minimum spanning tree
void KruskalMST(struct Graph* graph) {
    int numVertices = graph->numVertices;
    struct Edge result[numVertices - 1]; // Array to store the resultant MST
    int e = 0; // Index variable for result[]

    // Allocate memory for creating numVertices subsets
    int* parent = (int*)malloc(numVertices * sizeof(int));

    // Initialize all subsets as single element sets
    for (int v = 0; v < numVertices; ++v)
        parent[v] = -1;

    // Allocate memory for storing all edges
    struct Edge* edges = (struct Edge*)malloc(numVertices * numVertices * sizeof(struct Edge));
    int edgeIndex = 0;

    // Traverse the adjacency list to extract all edges
    for (int v = 0; v < numVertices; ++v) {
        struct Node* temp = graph->array[v].head;
        while (temp != NULL) {
            if (temp->vertex > v) { // To avoid adding the same edge twice
                edges[edgeIndex].src = v;
                edges[edgeIndex].dest = temp->vertex;
                edges[edgeIndex].weight = temp->weight;
                edgeIndex++;
            }
            temp = temp->next;
        }
    }
    // Sort all the edges in non-decreasing order of their weight
    qsort(edges, edgeIndex, sizeof(struct Edge), compare);

    // Number of edges to be taken is equal to numVertices-1
    for (int i = 0; i < edgeIndex; ++i) {
        int x = find(parent, edges[i].src);
        int y = find(parent, edges[i].dest);

        // If including this edge does't cause cycle, include it in result and increment the index of result for next edge
        if (x != y) {
            result[e++] = edges[i];
            Union(parent, x, y);
        }
    }
    // Print the minimum spanning tree
    printf("Edge   Weight\n");
    for (int i = 0; i < e; ++i)
        printf("%d - %d    %d \n", result[i].src, result[i].dest, result[i].weight);

    free(parent);
    free(edges);
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
    // Print the minimum spanning tree using Kruskal's algorithm
    printf("Minimum Spanning Tree using Kruskal's Algorithm:\n");
    KruskalMST(graph);
    return 0;
}
