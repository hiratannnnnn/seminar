#include "hamilton.h"

static int can_goto(Edge *head, int target)
{
    while (head)
    {
        if (head->to == target)
            return (1);
        head = head->next;
    }
    return (0);
}

static int is_all_visited(int *visited, int n)
{
    for (int i = 0; i < n; i++)
        if (visited[i] == 0)
            return (0);
    return (1);
}

static void print_path(PathNode *path)
{
    if (!path) return;
    printf("%d ", path->v->id);
    print_path(path->next);
}

static int	check_connection(Vertex **vs, int *visited, int n)
{
	int *queue = (int *)xcalloc(n, sizeof(int));
    int *seen = (int *)xcalloc(n, sizeof(int));
    int front = 0, rear = 0, count = 0, start = -1;

    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            start = i;
            break;
        }
    }
    if (start == -1) {
        xfree(queue, n * sizeof(int));
        xfree(seen, n * sizeof(int));
        return (1);
    }

    queue[rear++] = start;
    seen[start] = 1;
    count = 1;
    while (front < rear) {
        int v = queue[front++];
        for (Edge *e = vs[v]->incidence; e; e = e->next) {
            int to = e->to;
            if (visited[to] == 0 && !seen[to]) {
                seen[to] = 1;
                queue[rear++] = to;
                count++;
            }
        }
    }

    int unvisited = 0;
    for (int i = 0; i < n; i++)
        if (visited[i] == 0) unvisited++;

    xfree(queue, n * sizeof(int));
    xfree(seen, n * sizeof(int));
    return (count == unvisited);
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
            return (1);
        }
        return (0);
    }
	if (!check_connection(vs, visited, n))
		return (printf("edagari"), 0);
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
                return (1);
            }
            visited[edge->to] = 0;
            printf("[DEBUG] Returning to %d\n", edge->from);
            pathnode_pop_last(head);
        }
        edge = edge->next;
    }
    return (0);
}

int     solve	(Vertex **vs, int n)
{
    int *visited = (int *)xcalloc(n, sizeof(int));
    PathNode *list;
    list = NULL;
    if (!visited)
        return -1;
    visited[0] = 1;
    int result = backtrack(vs, visited, 0, n, &list);
    xfree(visited, sizeof(int) * n);
    free_path(&list);
    return result;
}
