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

// typedef struct
// {
// 	Extremity *from;
// 	Extremity *to;
// }	Adjacency;

typedef struct Component
{
	Extremity *start;
	Extremity *end;
	int type;
	int oriented;
	struct Component *prev;
	struct Component *next;
}		Component;

typedef struct Extremity_ctx
{
	Extremity **exts;
	Extremity *ext_l;
	Extremity *ext_r;
	int n;
	Component *head;
}	Extremity_ctx;

// utils.c
void		free_ext			(Extremity *ext);
void 		free_array_exts		(Extremity **exts, int n);
Extremity 	*create_ext			(int id, int sign);
int 		is_all_true			(int *array, int n);
Extremity 	*get_pair_of		(Extremity_ctx *ctx, Extremity *ext);
void		free_component		(Component *comp);
void		free_component_list	(Component *head);
Component 	*create_component	(void);

// utils_print.c
void 		print_array_exts	(Extremity **exts, int n);
void		print_components	(Component *head);
void		chase_exts			(Extremity_ctx *ctx, Extremity *ext, int *used);
void		print_chromosomes	(Extremity_ctx *ctx, int n);

// contexts.c
void		Extremity_free		(Extremity_ctx *ctx, int n);
int 		Extremity_init		(Extremity_ctx *ctx, int *perm, int n);

// operations.c
void		cut_exts			(Extremity *e1, Extremity *e2);
void		join_exts			(Extremity *e1, Extremity *e2);

#endif
