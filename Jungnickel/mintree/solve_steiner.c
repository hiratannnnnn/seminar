#include "mintree.h"
#include "path.h"

typedef struct Steiner_ctx
{
	double W;
	EdgeNode T;

}				Steiner_ctx;

static void steiner_free();

static int steiner_init();

void solve_steiner()
{
	if (!steiner_init())
		return ;

	
}
