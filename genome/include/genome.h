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
	int *perm;
	Component *head;
}	Extremity_ctx;

typedef struct Stack_int
{
	int nbr;
	struct Stack_int *prev;
	struct Stack_int *next;
}			Stack_int;

// components.c
void		free_component		(Component *comp);
void		free_component_list	(Component *head);
Component 	*create_component	(void);

// find_components.c
void 		find_components_1	(Extremity_ctx *ctx, int *maxes, int *mins, int n);

// preprocess.c
int 		preprocess			(Extremity_ctx *ctx, int *maxes, int *mins);

// solve.c
int 		solve_dcj			(int *perm, int n);

// stacks.c
void 		free_stack_node		(Stack_int *node);
void		free_stack			(Stack_int *head);
Stack_int 	*create_stack_node	(int nbr);
void 		push_stack			(Stack_int **head, int nbr);
Stack_int 	*pop_stack			(Stack_int **head);
int 		peek_stack			(Stack_int *head);

// utils.c
void		free_ext			(Extremity *ext);
void 		free_array_exts		(Extremity **exts, int n);
Extremity 	*create_ext			(int id, int sign);
int 		is_all_true			(int *array, int n);
Extremity 	*get_pair_of		(Extremity_ctx *ctx, Extremity *ext);
Extremity 	*get_index_of		(Extremity_ctx *ctx, int index);
int 		is_nullish			(Extremity_ctx *ctx, Extremity *ext);

// utils_print.c
void 		print_array_exts	(Extremity **exts, int n);
void		print_components	(Component *head);
void		chase_exts			(Extremity_ctx *ctx, Extremity *ext, int *used);
void		print_chromosomes	(Extremity_ctx *ctx, int n);
void 		print_stack			(Stack_int *head);

// utils_read.c
int 		*read_perm			(char *filename, int *n);

// contexts.c
void		Extremity_free		(Extremity_ctx *ctx, int n);
int 		Extremity_init		(Extremity_ctx *ctx, int *perm, int n);

// operations.c
void		cut_exts			(Extremity *e1, Extremity *e2);
void		join_exts			(Extremity *e1, Extremity *e2);

#endif
