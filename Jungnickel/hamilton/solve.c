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
    int i;

    for (i = 0; i < n; i++)
        if (visited[i] == 0)
            return (0);
    return (1);
}

static void print_path(PathNode *path)
{
    if (!path)
        return;
    printf("%d ", path->v->id);
    print_path(path->next);
}

static int	check_connection(Vertex **vs, int *visited, int n)
{
    Edge *e;
	int *queue, *seen;
    int front, rear, count, start, unvisited, to;
    int i, v;

    queue = (int *)xcalloc(n, sizeof(int));
    seen = (int *)xcalloc(n, sizeof(int));
    front = 0, rear = 0, count = 0, start = -1;
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            start = i;
            break;
        }
    }
    if (start == -1) 
    {
        xfree(queue, n * sizeof(int));
        xfree(seen, n * sizeof(int));
        return (1);
    }
    queue[rear++] = start;
    seen[start] = 1;
    count = 1;
    while (front < rear)
    {
        v = queue[front++];
        for (e = vs[v]->incidence; e; e = e->next)
        {
            to = e->to;
            if (visited[to] == 0 && !seen[to])
            {
                seen[to] = 1;
                queue[rear++] = to;
                count++;
            }
        }
    }
    unvisited = 0;
    for (i = 0; i < n; i++)
        if (visited[i] == 0) unvisited++;
    free_array_int(queue, n);
    free_array_int(seen, n);
    return (count == unvisited);
}

static int backtrack(Vertex **vs, int *visited, int s, int n, PathNode **head)
{
    Vertex *v;
    Edge *edge;
    PathNode *node;

    v = vs[s];
    edge = v->incidence;
    node = create_pathnode(v);
    append_pathnode(head, node);
    if (is_all_visited(visited, n))
    {
        if (can_goto(edge, 0))
        {
            print_path(*head);
            return (1);
        }
        return (0);
    }
	if (!check_connection(vs, visited, n))
		return (0);
    while (edge)
    {
        if (visited[edge->to] == 0)
        {
            visited[edge->to] = 1;
            if (backtrack(vs, visited, edge->to, n, head))
                return (1);
            visited[edge->to] = 0;
            pathnode_pop_last(head);
        }
        edge = edge->next;
    }
    return (0);
}

int     solve	(Vertex **vs, int n)
{
    PathNode *list;
    int *visited;
    int result;
    
    visited = (int *)xcalloc(n, sizeof(int));
    if (!visited)
        return -1;
    list = NULL;
    visited[0] = 1;
    result = backtrack(vs, visited, 0, n, &list);
    free_array_int(visited, n);
    free_path(&list);
    return result;
}
