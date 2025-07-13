#include "path.h"

typedef struct 
{
    int *T;
    int *d;
    int T_count;
}		Dijkstra_ctx;

static void dijkstra_free(Dijkstra_ctx *ctx, int n)
{
    if (ctx->T)
        free_array_int(ctx->T, n);
    if (ctx->d)
        free_array_int(ctx->d, n);
}

static int dijkstra_init(Dijkstra_ctx *ctx, int n)
{
    int i;
    ctx->T = (int *)xmalloc(sizeof(int) * n);
    ctx->d = (int *)xmalloc(sizeof(int) * n);
    if (!ctx->T || !ctx->d)
    {
        dijkstra_free(ctx, n);
        return (0);
    }
    for (i = 0; i < n; i++)
    {
        ctx->T[i] = 1;
        ctx->d[i] = INT_MAX / 2;
    }
    ctx->T_count = n;
    return 1;
}

static int min_of_T_index(int *arr, int *T, int n)
{
    int min, i, index;
    min = INT_MAX;
    index = -1;

    for (i = 0; i < n; i++)
    {
        if (T[i] == 1 && arr[i] < min)
        {
            index = i;
            min = arr[i];
        }
    }
    return index;
}


void    solve_dijkstra(Vertex **vs, int s, int n)
{
    Dijkstra_ctx ctx;
    Edge *edge;
    int u, v;

    if (!dijkstra_init(&ctx, n))
        return ;
    ctx.d[s] = 0;
    while (ctx.T_count > 0)
    {
        u = min_of_T_index(ctx.d, ctx.T, n);
        printf("u: %d\n", u);
        ctx.T[u] = 0;
        ctx.T_count--;
        edge = vs[u]->incidence;
        while (edge)
        {
            v = edge->to;
            if (ctx.T[v])
            {
                printf("comparing %d and %d + %f\n", ctx.d[v], ctx.d[u], edge->cost);
                ctx.d[v] = min_int(ctx.d[v], (int)(ctx.d[u] + edge->cost));
            }
            edge = edge->next;
        }
        print_array_int(ctx.d, n, 11);
    }
    dijkstra_free(&ctx, n);
}