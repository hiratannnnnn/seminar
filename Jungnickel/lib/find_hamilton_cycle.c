#include "lib.h"

static void free_ctx(Hamilton_ctx *ctx, int n);

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

static int backtrack_hamilton(Hamilton_ctx *ctx, int cur, int n)
{
    Vertex      *v;
    Edge        *edge;
    PathNode    *node;

    sort_list_by_degree(&ctx->vs[cur]->incidence, ctx->degree, cmp_int_asc);
    v 		= ctx->vs[cur];
    edge	= v->incidence;
    node	= create_pathnode(v);
    append_pathnode(&ctx->head, node);
    if (is_all_visited(ctx->visited, n))
    {
        if (can_goto(edge, 0))
            return (1);
        return (0);
    }
    while (edge)
    {
        if (ctx->visited[edge->to] == 0)
        {
            ctx->visited[edge->to] = 1;
            if (backtrack_hamilton(ctx, edge->to, n))
                return (1);
            ctx->visited[edge->to] = 0;
            pathnode_pop_last(&ctx->head);
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

static void free_ctx(Hamilton_ctx *ctx, int n)
{
    if (ctx->degree)
    {
        free_array_int(ctx->degree, n);
        ctx->degree = NULL;
    }
    if (ctx->visited)
    {
        free_array_int(ctx->visited, n);
        ctx->visited = NULL;
    }
    if (ctx->head)
        free_path(&ctx->head);
}

int find_hamilton_cycle(Vertex **vs, int n)
{
    Hamilton_ctx ctx;
    int init;
	int result;
    init = hamilton_ctx_init(&ctx, vs, n);
    if (init < 1)
        return (init);
    ctx.visited[0] 	= 1;
    result 		= backtrack_hamilton(&ctx, 0, n);
    free_ctx(&ctx, n);
    return (result);
}
