#include "../jung.h"

/**
 * @brief Prints the Euler tour showing edge IDs
 *
 * @param tour The Euler tour as a linked list of edges
 */
void print_euler_tour_edges(Node *tour)
{
    Node *cur;

    if (!tour)
    {
        printf("Euler tour is empty\n");
        return;
    }

    cur = tour;
    printf("Euler tour (edge IDs): ");
    while (cur)
    {
        printf("%d", cur->edge_id);
        if (cur->next)
            printf(" -> ");
        cur = cur->next;
    }
    printf("\n");
}

/**
 * @brief Prints the Euler tour showing vertices
 *
 * @param tour The Euler tour as a linked list of edges
 * @param vs Array of vertex structures
 */
void print_euler_tour_vertices(Node *tour, Vertex **vs)
{
    Node *cur;
    int current_vertex = -1;
    Edge *edge;
    int i, found;

    if (!tour)
    {
        printf("Euler tour is empty\n");
        return;
    }

    // Find starting vertex (any vertex incident with the first edge)
    cur = tour;
    for (i = 0; i < 100; i++)  // Assuming fewer than 100 vertices
    {
        if (!vs[i])
            continue;

        found = 0;
        edge = vs[i]->incidence;
        while (edge)
        {
            if (edge->id == cur->edge_id)
            {
                current_vertex = i;
                found = 1;
                break;
            }
            edge = edge->next;
        }
        if (found)
            break;
    }

    if (current_vertex == -1)
    {
        printf("Error: Could not find starting vertex\n");
        return;
    }

    // Print the tour
    printf("Euler tour (vertices): %d", current_vertex);

    cur = tour;
    while (cur)
    {
        // Find the next vertex (the other end of the current edge from current_vertex)
        edge = vs[current_vertex]->incidence;
        found = 0;
        while (edge)
        {
            if (edge->id == cur->edge_id)
            {
                current_vertex = edge->to;
                printf(" -> %d", current_vertex);
                found = 1;
                break;
            }
            edge = edge->next;
        }

        if (!found)
            printf(" -> ?");  // Error case: edge not found

        cur = cur->next;
    }
    printf("\n");
}

/**
 * @brief Converts an Euler tour to an edge list
 *
 * @param tour Linked list of edges representing the Euler tour
 * @param edges Pointer to array that will hold edge IDs
 * @param edge_count Pointer to variable that will hold the number of edges
 */
void euler_tour_to_edge_list(Node *tour, int **edges, int *edge_count)
{
    Node *current = tour;
    int count = 0;
    int *edge_list;

    // Count edges in tour
    while (current)
    {
        count++;
        current = current->next;
    }

    // Allocate edge list
    edge_list = (int *)malloc(count * sizeof(int));
    if (!edge_list)
    {
        *edges = NULL;
        *edge_count = 0;
        return;
    }

    // Fill edge list
    current = tour;
    count = 0;
    while (current)
    {
        edge_list[count++] = current->edge_id;
        current = current->next;
    }

    *edges = edge_list;
    *edge_count = count;
}

/**
 * @brief Checks if a tour is an Euler tour
 *
 * @param tour The tour to check
 * @param vs Array of vertex structures
 * @param n Number of vertices
 * @return 1 if the tour is an Euler tour, 0 otherwise
 */
int is_euler_tour(Node *tour, Vertex **vs, int n)
{
    int *used_edges;
    int edge_count = 0;
    int total_edges = 0;
    Node *current;
    Edge *edge;
    int i;

    // Count total edges in the graph
    for (i = 0; i < n; i++)
    {
        edge = vs[i]->incidence;
        while (edge)
        {
            if (edge->from <= edge->to)  // Count each edge only once
                total_edges++;
            edge = edge->next;
        }
    }

    // Allocate array to track used edges
    used_edges = (int *)calloc(total_edges, sizeof(int));
    if (!used_edges)
        return 0;

    // Mark edges used in the tour
    current = tour;
    while (current)
    {
        if (current->edge_id < total_edges)
            used_edges[current->edge_id] = 1;
        current = current->next;
        edge_count++;
    }

    // Check if all edges are used exactly once
    int all_used = 1;
    for (i = 0; i < total_edges; i++)
    {
        if (!used_edges[i])
        {
            all_used = 0;
            break;
        }
    }

    free(used_edges);

    // An Euler tour must use all edges exactly once
    return (all_used && edge_count == total_edges);
}

/**
 * @brief Writes the Euler tour as a vertex sequence to a file
 *
 * @param tour The Euler tour as a linked list of edges
 * @param vs Array of vertex structures
 * @param filename Output file name
 * @return 1 if successful, 0 otherwise
 */
int write_euler_tour_vertices(Node *tour, Vertex **vs, const char *filename)
{
    FILE *fp;
    Node *cur;
    int current_vertex = -1;
    Edge *edge;
    int i, found;

    if (!tour || !vs || !filename)
        return 0;

    // Find starting vertex (any vertex incident with the first edge)
    cur = tour;
    for (i = 0; i < 100; i++)  // Assuming fewer than 100 vertices
    {
        if (!vs[i])
            continue;

        found = 0;
        edge = vs[i]->incidence;
        while (edge)
        {
            if (edge->id == cur->edge_id)
            {
                current_vertex = i;
                found = 1;
                break;
            }
            edge = edge->next;
        }
        if (found)
            break;
    }

    if (current_vertex == -1)
        return 0;

    fp = fopen(filename, "w");
    if (!fp)
        return 0;

    // Write the tour
    fprintf(fp, "%d", current_vertex);

    cur = tour;
    while (cur)
    {
        // Find the next vertex (the other end of the current edge from current_vertex)
        edge = vs[current_vertex]->incidence;
        found = 0;
        while (edge)
        {
            if (edge->id == cur->edge_id)
            {
                current_vertex = edge->to;
                fprintf(fp, " %d", current_vertex);
                found = 1;
                break;
            }
            edge = edge->next;
        }
        if (!found)
            fprintf(fp, " ?");
        cur = cur->next;
    }
    fprintf(fp, "\n");
    fclose(fp);
    return 1;
}
