#ifndef GENOME_H
# define GENOME_H

# include "libgenome.h"

typedef struct Extremity
{
	int id;	// 1 ...
	int sign;		// 1 or -1
	struct Extremity *reality;	// A
	struct Extremity *desire;	// B
}	Extremity;

typedef struct
{
	Extremity *from;
	Extremity *to;
}	Adjacency;

typedef struct Extremity_ctx
{
	Extremity **exts;
	Extremity *ext_l;
	Extremity *ext_r;
	int n;
}	Extremity_ctx;

#endif
