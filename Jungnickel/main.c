#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jung.h"

void print_usage() {
    printf("Usage:\n");
    printf("  ./jung degrees <d1> <d2> ... <dn>  - Generate graph from degree sequence\n");
    printf("  ./jung prufer <p1> <p2> ... <pn>   - Calculate degree sequence from Prufer code\n");
    printf("Examples:\n");
    printf("  ./jung degrees 1 1 1 1 4           - Generate graph from degree sequence [1,1,1,1,4]\n");
    printf("  ./jung prufer 4 4 4 5              - Calculate degree sequence from Prufer code [4,4,4,5]\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage();
        return 1;
    }

    // Parse command line arguments
    char *command = argv[1];
    int *values;
    int n, i, j, sum = 0;
    
    // Prepare values array
    n = argc - 2;
    values = (int *)malloc(sizeof(int) * n);
    
    for (i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 2]);
    }
    
    if (strcmp(command, "degrees") == 0) {
        // Generate graph from degree sequence
        
        // Check sum of degrees
        for (i = 0; i < n; i++) {
            sum += values[i];
        }
        
        if (sum != 2 * (n - 1)) {
            printf("Error: Sum of degrees (%d) does not equal 2(n-1) = %d\n", sum, 2 * (n - 1));
            free(values);
            return 1;
        }
        
        printf("Degree Sequence: ");
        for (i = 0; i < n; i++) {
            printf("%d ", values[i]);
        }
        printf("\n");
        
        // Generate Prufer code from degree sequence
        int *prufer = generate_prufer_code(values, n);
        if (prufer) {
            printf("\nGenerated Prufer Code: ");
            for (i = 0; i < n - 2; i++) {
                printf("%d ", prufer[i] + 1);  // 1-indexed display
            }
            printf("\n");
            
            free(prufer);
        }
        
        // Generate adjacency matrix from degree sequence
        int **matrix = generate_matrix(values, n);
        
        printf("\nAdjacency Matrix:\n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        
        // Draw the graph
        draw_graph(matrix, n);
        
        // Verify if adjacency matrix represents a tree
        printf("\nTree Verification:\n");
        int edge_count = 0;
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                if (matrix[i][j]) {
                    edge_count++;
                }
            }
        }
        printf("Number of vertices: %d\n", n);
        printf("Number of edges: %d\n", edge_count);
        if (is_tree(matrix, n)) {
            printf("Result: This adjacency matrix represents a tree.\n");
        } else {
            printf("Result: This adjacency matrix does not represent a tree.\n");
        }
        
        // Free memory
        for (i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        
    } else if (strcmp(command, "prufer") == 0) {
        // Calculate degree sequence from Prufer code
        
        printf("Prufer Code: ");
        for (i = 0; i < n; i++) {
            printf("%d ", values[i]);
        }
        printf("\n");
        
        // Convert to 0-indexed
        for (i = 0; i < n; i++) {
            values[i]--;
        }
        
        // Calculate degree sequence
        int *degrees = count_degrees(values, n);
        int vertices = n + 2;
        
        printf("\nCalculated Degree Sequence:\n");
        for (i = 0; i < vertices; i++) {
            printf("Vertex %d: %d\n", i + 1, degrees[i]);
        }
        
        // Generate adjacency matrix
        int **matrix = generate_matrix(degrees, vertices);
        
        printf("\nAdjacency Matrix:\n");
        for (i = 0; i < vertices; i++) {
            for (j = 0; j < vertices; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        
        // Draw the graph
        draw_graph(matrix, vertices);
        
        // Verify if adjacency matrix represents a tree
        printf("\nTree Verification:\n");
        int edge_count = 0;
        for (i = 0; i < vertices; i++) {
            for (j = i + 1; j < vertices; j++) {
                if (matrix[i][j]) {
                    edge_count++;
                }
            }
        }
        printf("Number of vertices: %d\n", vertices);
        printf("Number of edges: %d\n", edge_count);
        if (is_tree(matrix, vertices)) {
            printf("Result: This adjacency matrix represents a tree.\n");
        } else {
            printf("Result: This adjacency matrix does not represent a tree.\n");
        }
        
        // Free memory
        for (i = 0; i < vertices; i++) {
            free(matrix[i]);
        }
        free(matrix);
        free(degrees);
        
    } else {
        printf("Unknown command: %s\n", command);
        print_usage();
        free(values);
        return 1;
    }
    
    free(values);
    return 0;
}