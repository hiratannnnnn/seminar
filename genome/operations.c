#include "genome.h"

void	cut_exts(Extremity *e1, Extremity *e2)
{
	if (e1->reality != e2 || e2->reality != e1)
	{
		printf("Cannot cut disconnected ones.\n");
		return ;
	}
	e1->reality = NULL;
	e2->reality = NULL;
}

void	join_exts(Extremity *e1, Extremity *e2)
{
	if (e1->reality != NULL || e2->reality != NULL)
	{
		printf("Cut the edge first.\n");
		return ;
	}
	e1->reality = e2;
	e2->reality = e1;
}

// void	randomize_chromosome()
