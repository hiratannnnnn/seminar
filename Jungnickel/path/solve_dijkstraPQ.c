#include "path.h"

typedef struct
{
    int     *dist;
    int     *T;
    Node    *queue;
}		DijkstraPQ_ctx;

static void dijkstraPQ_free(DijkstraPQ_ctx *ctx, int n)
{
}

static int dijkstraPQ_init(DijkstraPQ_ctx *ctx, int n)
{
    return 1;
}

void    solve_dijkstraPQ(Vertex **vs, int s, int n)
{

}