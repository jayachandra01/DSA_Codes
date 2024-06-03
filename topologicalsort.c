#include <stdio.h>
#include <stdlib.h>

// A structure to represent an adjacency list node
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// A structure to represent a graph
struct Graph {
    int V;
    struct AdjList* array;
    int* inDegree;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists. Size of array will be V
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    // Initialize in-degrees
    graph->inDegree = (int*)calloc(V, sizeof(int));

    return graph;
}

// Function to add an edge to a directed graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest. A new node is added to the adjacency list of src
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Increase in-degree of destination vertex
    graph->inDegree[dest]++;
}

// A recursive function used by topologicalSortDFS
void topologicalSortUtil(int v, int visited[], int* stack, int* stackIndex, struct Graph* graph) {
    // Mark the current node as visited
    visited[v] = 1;

    // Recur for all the vertices adjacent to this vertex
    struct AdjListNode* node = graph->array[v].head;
    while (node != NULL) {
        if (!visited[node->dest]) {
            topologicalSortUtil(node->dest, visited, stack, stackIndex, graph);
        }
        node = node->next;
    }

    // Push current vertex to stack which stores the result
    stack[(*stackIndex)++] = v;
}

// The function to do Topological Sort using DFS. It uses topologicalSortUtil()
void topologicalSortDFS(struct Graph* graph) {
    int* stack = (int*)malloc(graph->V * sizeof(int));
    int stackIndex = 0;

    // Mark all the vertices as not visited
    int* visited = (int*)calloc(graph->V, sizeof(int));

    // Call the recursive helper function to store Topological Sort starting from all vertices one by one
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack, &stackIndex, graph);
        }
    }

    // Print the contents of the stack
    printf("Topological Sort (DFS):\n");
    for (int i = stackIndex - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(stack);
    free(visited);
}

// Function to perform Topological Sort using Source Removal Technique
void topologicalSortSourceRemoval(struct Graph* graph) {
    int* sortedOrder = (int*)malloc(graph->V * sizeof(int));
    int index = 0;

    // Queue to store the vertices with in-degree 0
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    // Enqueue all vertices with in-degree 0
    for (int i = 0; i < graph->V; i++) {
        if (graph->inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front != rear) {
        int v = queue[front++];
        sortedOrder[index++] = v;

        // For all adjacent vertices of v, reduce their in-degree by 1
        struct AdjListNode* node = graph->array[v].head;
        while (node != NULL) {
            int adjVertex = node->dest;
            graph->inDegree[adjVertex]--;
            if (graph->inDegree[adjVertex] == 0) {
                queue[rear++] = adjVertex;
            }
            node = node->next;
        }
    }

    // Check if there was a cycle
    if (index != graph->V) {
        printf("Graph has a cycle. Topological sort not possible.\n");
    } else {
        printf("Topological Sort (Source Removal):\n");
        for (int i = 0; i < index; i++) {
            printf("%d ", sortedOrder[i]);
        }
        printf("\n");
    }

    free(sortedOrder);
    free(queue);
}

int main() {
    int V, E, src, dest, choice;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    struct Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);
    
    for (int i = 0; i < E; ++i) {
        printf("Enter source and destination of edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Choose Topological Sort Method:\n");
    printf("1. Depth-First Search (DFS)\n");
    printf("2. Source Removal\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            topologicalSortDFS(graph);
            break;
        case 2:
            topologicalSortSourceRemoval(graph);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    // Free allocated memory
    for (int i = 0; i < V; ++i) {
        struct AdjListNode* node = graph->array[i].head;
        while (node != NULL) {
            struct AdjListNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph->inDegree);
    free(graph);

    return 0;
}
