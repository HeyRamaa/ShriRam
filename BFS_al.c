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
// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
// Function to perform Breadth-First Search (BFS) traversal
void BFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i)
        visited[i] = 0;
    // Create a queue for BFS
    struct Queue {
        int front, rear;
        int capacity;
        int* array;
    };
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = graph->numVertices;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    // Enqueue the start vertex and mark it as visited
    queue->array[++queue->rear] = startVertex;
    visited[startVertex] = 1;
    printf("BFS Traversal starting from vertex %d: ", startVertex);
    while (queue->front != queue->rear + 1) {
        int currentVertex = queue->array[++queue->front];
        printf("%d ", currentVertex);
        // Traverse the adjacency list of current vertex and enqueue its adjacent vertices
        struct Node* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                queue->array[++queue->rear] = adjVertex;
                visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
    free(visited);
    free(queue->array);
    free(queue);
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
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);
    struct Graph* graph = createGraph(numVertices);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);
    for (int i = 0; i < numEdges; ++i) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    printGraph(graph);
    int startVertex;
    printf("\nEnter the starting vertex for BFS traversal: ");
    scanf("%d", &startVertex);
    BFS(graph, startVertex);
    return 0;
}
