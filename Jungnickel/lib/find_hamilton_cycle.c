#include "lib.h"

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

static int backtrack(Vertex **vs, int *visited, int s, int n, PathNode **head)
{
    Vertex      *v;
    Edge        *edge;
    PathNode    *node;

    v 		= vs[s];
    edge	= v->incidence;
    node	= create_pathnode(v);
    append_pathnode(head, node);
    if (is_all_visited(visited, n))
    {
        if (can_goto(edge, 0))
            return (1);
        return (0);
    }
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

int find_hamilton_cycle(Vertex **vs, int n)
{
    int         *visited;
    PathNode    *list;
	int         result;

	visited     = (int *)xcalloc(n, sizeof(int));
    if (!visited)
		return -1;
    list 		= NULL;
    visited[0] 	= 1;
    result 		= backtrack(vs, visited, 0, n, &list);
    xfree(visited, sizeof(int) * n);
    free_path(list);
    return (result);
}
