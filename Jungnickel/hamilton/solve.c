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
    printf("%d ", path->v->id);
    print_path(path->next);
}

static int backtrack(Vertex **vs, int *visited, int s, int n, PathNode **head)
{
    Vertex *v = vs[s];
    Edge *edge = v->incidence;

    PathNode *node = create_pathnode(v);
    append_pathnode(head, node);

    if (is_all_visited(visited, n))
    {
        if (can_goto(edge, 0))
        {
            print_path(*head);
            printf("0\n");
            return 1;
        }
        return 0;
    }
    while (edge)
    {
        if (visited[edge->to] == 0)
        {
            visited[edge->to] = 1;
            printf("[DEBUG] ");
            print_path(*head);
            printf("\n[DEBUG] Moving to %d\n", edge->to);
            if (backtrack(vs, visited, edge->to, n, head))
            {
                return 1;
            }
            visited[edge->to] = 0;
            printf("[DEBUG] Returning to %d\n", edge->from);
            pathnode_pop_last(head);
        }
        edge = edge->next;
    }
    return 0;
}

int solve(Vertex **vs, int n)
{
    int *visited = (int *)xcalloc(n, sizeof(int));
    PathNode *list;
    list = NULL;
    if (!visited)
        return -1;
    visited[0] = 1;
    int result = backtrack(vs, visited, 0, n, &list);
    xfree(visited, sizeof(int) * n);
    free_path(list);
    return result;
}
