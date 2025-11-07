#ifndef GENOME_H
# define GENOME_H

# include "libgenome.h"

typedef struct Extremity
{
	int gene_id;	// 1 ...
	int sign;		// 1 or -1
	struct Extremity *reality;	// A
	struct Extremity *desire;	// B
}	Extremity;

typedef struct
{
	Extremity *from;
	Extremity *to;
}	Adjacency;

#endif
