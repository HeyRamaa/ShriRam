#include <stdio.h>
#include <stdlib.h>
// Structure for a node in adjacency list
struct Node {
    int vertex;
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
};
// Function to create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
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
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // For an undirected graph, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
// Function to perform Depth-First Search (DFS) traversal
void DFS(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    // Traverse the adjacency list of the current vertex
    struct Node* temp = graph->array[vertex].head;
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
            DFS(graph, adjVertex, visited);
        temp = temp->next;
    }
}
// Function to print the adjacency list representation of the graph
void printGraph(struct Graph* graph) {
    printf("Adjacency List Representation of the Graph:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* temp = graph->array[i].head;
        printf("Vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int numVertices, numEdges, src, dest;
    printf("Enter number of vertices in the graph: ");
    scanf("%d", &numVertices);
    struct Graph* graph = createGraph(numVertices);
    printf("Enter number of edges in the graph: ");
    scanf("%d", &numEdges);
    for (int i = 0; i < numEdges; ++i) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    printGraph(graph);
    // Perform DFS traversal starting from vertex 0
    int* visited = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; ++i)
        visited[i] = 0;
    printf("\nDFS Traversal starting from vertex 0: ");
    DFS(graph, 0, visited);

    free(visited);
    return 0;
}
