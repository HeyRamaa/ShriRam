#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};
// Structure to represent a graph
struct Graph {
    int numVertices, numEdges;
    int** matrix; // Adjacency matrix
};
// Function to create a graph with 'numVertices' vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    graph->matrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        graph->matrix[i] = (int*)calloc(numVertices, sizeof(int));
    }
    return graph;
}
// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->matrix[src][dest] = weight;
    graph->matrix[dest][src] = weight;
    graph->numEdges++;
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
    struct Edge result[numVertices]; // Array to store the resultant MST
    int e = 0; // Index variable for result[]
    // Step 1: Sort all the edges in non-decreasing order of their weight
    struct Edge* edges = (struct Edge*)malloc(graph->numEdges * sizeof(struct Edge));
    int edgeIndex = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (graph->matrix[i][j] != 0) {
                edges[edgeIndex].src = i;
                edges[edgeIndex].dest = j;
                edges[edgeIndex].weight = graph->matrix[i][j];
                edgeIndex++;
            }
        }
    }
    qsort(edges, graph->numEdges, sizeof(struct Edge), compare);
    // Allocate memory for creating numVertices subsets
    int* parent = (int*)malloc(numVertices * sizeof(int));
    // Initialize all subsets as single element sets
    for (int v = 0; v < numVertices; ++v)
        parent[v] = -1;
    // Number of edges to be taken is equal to numVertices-1
    while (e < numVertices - 1) {
        // Step 2: Pick the smallest edge and increment the index for next iteration
        struct Edge nextEdge = edges[e++];
        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);
        // If including this edge does't cause cycle, include it in result and increment the index of result for next edge
        if (x != y) {
            result[e - 1] = nextEdge;
            Union(parent, x, y);
        }
    }
    // Print the minimum spanning tree
    printf("Edge   Weight\n");
    for (int i = 0; i < e - 1; ++i)
        printf("%d - %d    %d \n", result[i].src, result[i].dest, result[i].weight);
    free(edges);
    free(parent);
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
