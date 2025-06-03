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

static int hamilton_ctx_init(Hamilton_ctx *ctx, Vertex **vs, int n)
{
    ctx->degree = xmalloc(sizeof(int) * n);
    if (!ctx->degree)
        return (-2);
    compute_degrees_from_list(vs, n, ctx->degree);
    ctx->visited = xmalloc(sizeof(int) * n);
    ctx->vs = vs;
    if (!ctx->visited || !ctx->vs)
        return (free_ctx(ctx, n), -2);
    ctx->head = NULL;
    return (1);
}

static void free_ctx(Euler_ctx *ctx, int n)
{
    
}

int find_hamilton_cycle(Vertex **vs, int n)
{
    Hamilton_ctx ctx;
    int init;
    init = hamilton_ctx_init(&ctx, vs, n);
	int         result;

    ctx.visited[0] 	= 1;
    result 		= backtrack(ctx,  0, n);
    xfree(, sizeof(int) * n);
    free_path(&ctx.head);
    return (result);
}
