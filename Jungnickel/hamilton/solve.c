#include "hamilton.h"

static int can_goto(Edge *head, int target)
{
    while (head)
    {
        if (head->to == target)
            return 1;
        head = head->next;
    }
    return 0;
}

static int is_all_visited(int *visited, int n)
{
    for (int i = 0; i < n; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

static void print_path(PathNode *path)
{
    if (!path) return;
    print_path(path->next);
    printf("%d ", path->v->id);
}

static int backtrack(Vertex **vs, int *visited, int s, int n, PathNode *path)
{
    Vertex *v = vs[s];
    Edge *edge = v->incidence;

    PathNode *node = create_pathnode(v);
    node->next = path;
    path = node;

    if (is_all_visited(visited, n))
    {
        if (can_goto(edge, 0))
        {
            print_path(path);
            printf("0\n");
            free_path(path);
            return 1;
        }
        free_path(path);
        return 0;
    }
    while (edge)
    {
        if (visited[edge->to] == 0)
        {
            visited[edge->to] = 1;
            if (backtrack(vs, visited, edge->to, n, path))
            {
                // free_path(path);
                return 1;
            }
            visited[edge->to] = 0;
        }
        edge = edge->next;
    }
    free_path(path);
    return 0;
}

int solve(Vertex **vs, int n)
{
    int *visited = (int *)xcalloc(n, sizeof(int));
    if (!visited)
        return -1;
    visited[0] = 1;
    int result = backtrack(vs, visited, 0, n, NULL);
    xfree(visited, sizeof(int) * n);
    return result;
}
