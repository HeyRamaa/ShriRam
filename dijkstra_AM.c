#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
int minDistance(int dist[], bool sptSet[], int numVertices) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < numVertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}
// Function to print the constructed distance array
void printSolution(int dist[], int numVertices) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < numVertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
void dijkstra(int graph[][100], int src, int dest, int numVertices) {
    int dist[numVertices]; // The output array. dist[i] will hold the shortest distance from src to i
    bool sptSet[numVertices]; // sptSet[i] will be true if vertex i is included in the shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < numVertices; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < numVertices - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        // u is always equal to src in the first iteration
        int u = minDistance(dist, sptSet, numVertices);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < numVertices; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the shortest distance between the source and destination vertices
    printf("Shortest distance between %d and %d: %d\n", src, dest, dist[dest]);
}

int main() {
    int numVertices, numEdges, src, dest, weight;
    printf("Enter number of vertices in the graph: ");
    scanf("%d", &numVertices);
    int graph[100][100] = {{0}}; // Initialize adjacency matrix with zeros
    printf("Enter number of edges in the graph: ");
    scanf("%d", &numEdges);
    for (int i = 0; i < numEdges; ++i) {
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);
    printf("Enter destination vertex: ");
    scanf("%d", &dest);

    dijkstra(graph, src, dest, numVertices);

    return 0;
}
