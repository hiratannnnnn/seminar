#include "path.h"

typedef struct
{
    int     *dist;
    int     *T;
    Heap    *queue;
}		DijkstraPQ_ctx;

// 比較関数: Vertexのidを使ってdistで比較
static int node_cmp(const void *a, const void *b)
{
    const Node *na = a, *nb = b;
    Vertex *va = (Vertex *)(na->ptr);
    Vertex *vb = (Vertex *)(nb->ptr);
    extern int *global_dist;
    return global_dist[va->id] - global_dist[vb->id];
}

static void dijkstraPQ_free(DijkstraPQ_ctx *ctx, int n)
{
    if (ctx->dist) free_array_int(ctx->dist, n);
    if (ctx->T) free_array_int(ctx->T, n);
    if (ctx->queue) heap_free(ctx->queue, 3);
}

static int dijkstraPQ_init(DijkstraPQ_ctx *ctx, int n)
{
    ctx->dist = xmalloc(sizeof(int) * n);
    ctx->T = xmalloc(sizeof(int) * n);
    ctx->queue = NULL;
    if (!ctx->dist || !ctx->T)
        return 0;
    for (int i = 0; i < n; i++) {
        ctx->dist[i] = INT_MAX / 2;
        ctx->T[i] = 1;
    }
    return 1;
}

int *global_dist = NULL;

void solve_dijkstraPQ(Vertex **vs, int s, int n)
{
    DijkstraPQ_ctx ctx;
    if (!dijkstraPQ_init(&ctx, n))
        return;

    global_dist = ctx.dist;
    ctx.dist[s] = 0;
    ctx.queue = heap_create(n * 2, node_cmp);

    // 始点をキューに追加
    Node *start_node = xmalloc(sizeof(Node));
    start_node->ptr = vs[s];
    start_node->type = NODE_TYPE_VERTEX;
    start_node->prev = NULL;
    start_node->next = NULL;
    heap_push(ctx.queue, start_node);

    while (ctx.queue->size > 0)
    {
        Node *node = heap_pop(ctx.queue);
        Vertex *u = (Vertex *)(node->ptr);
        int uid = u->id;
        if (!ctx.T[uid]) {
            free(node);
            continue;
        }
        ctx.T[uid] = 0;

        Edge *edge = u->incidence;
        while (edge)
        {
            Vertex *v = vs[edge->to];
            int vid = v->id;
            if (ctx.T[vid])
            {
                int new_dist = ctx.dist[uid] + (int)edge->cost;
                if (new_dist < ctx.dist[vid])
                {
                    ctx.dist[vid] = new_dist;
                    Node *new_node = xmalloc(sizeof(Node));
                    new_node->ptr = v;
                    new_node->type = NODE_TYPE_VERTEX;
                    new_node->prev = NULL;
                    new_node->next = NULL;
                    heap_push(ctx.queue, new_node);
                }
            }
            edge = edge->next;
        }
        free(node);
    }

    print_array_int(ctx.dist, n, 11);
    dijkstraPQ_free(&ctx, n);
    global_dist = NULL;
}