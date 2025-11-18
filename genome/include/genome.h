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

typedef struct Adjacency
{
	Extremity *left;
	Extremity *right;
	struct Adjacency *left_to;
	struct Adjacency *right_to;
	int visited;
}	Adjacency;

typedef struct
{
	int *ends;
	int *starts;
}	Components;

typedef struct Extremity_ctx
{
	Extremity **exts;
	Extremity *ext_l;
	Extremity *ext_r;
	Extremity **goals;
	Extremity *goal_l;
	Extremity *goal_r;
	int n;
	int *perm;
	int *sigma;
	int n_sent;
	int nb_sent;
	int *perm_sent;
	int *sigma_sent;
	int *pb_sent;
	int *sb_sent;
}	Extremity_ctx;

typedef struct Stack_int
{
	int nbr;
	struct Stack_int *prev;
	struct Stack_int *next;
}			Stack_int;

// contexts.c
void		put_desires			(Extremity **exts, Extremity *ext_l, Extremity *ext_r, int n);
void		put_realities		(Extremity_ctx *ctx, Extremity **exts, Extremity *ext_l, Extremity *ext_r, int *perm, int n);
void		Extremity_free		(Extremity_ctx *ctx, int n);
int 		Extremity_init		(Extremity_ctx *ctx, int *perm, int n);
Extremity 	**perm_to_exts		(int *perm, int n);
void		print_Extremity_ctx	(Extremity_ctx *ctx);

// examples.c
int 		write_perm_ext		(int *perm, int n, double cut_prob, char const *filename);
int 		make_example		(int n, char const *filename, double cut_prob);

// find_components.c
void 		find_components_1	(Extremity_ctx *ctx, int *maxes, int *mins, Components *cmps);

// preprocess.c
int 		preprocess			(Extremity_ctx *ctx, int *maxes, int *mins);

// solve.c
int 		solve_dcj_mine		(Extremity_ctx *ctx);
int 		solve_dcj			(Extremity_ctx *ctx);

// utils.c
int 		is_all_true			(int *array, int n);
int 		is_nullish			(Extremity_ctx *ctx, Extremity *ext);
void		reverse_p			(Extremity_ctx *ctx, int *perm, int *sigma);

// utils_adj.c
Adjacency 	*create_adj_node	(Extremity *left, Extremity *right);
void		free_list_adj		(Adjacency **list, int n);

// utils_ext.c
void		free_ext			(Extremity *ext);
void 		free_array_exts		(Extremity **exts, int n);
Extremity 	*create_ext			(int id, int sign);
Extremity 	*get_pair_of		(Extremity_ctx *ctx, Extremity *ext);
Extremity 	*get_ext_by_perm_index		(Extremity_ctx *ctx, Extremity **exts, int index);
Extremity 	*get_ext_by_value			(Extremity_ctx *ctx, Extremity **exts, int value);
int 		get_value_ext		(Extremity_ctx *ctx, Extremity *ext);
void		cut_exts			(Extremity_ctx *ctx, Extremity *e1, Extremity *e2);

// utils_print.c
void 		print_array_exts	(Extremity **exts, int n);
void		print_components	(Extremity_ctx *ctx, Components *cmps);
void		print_perm_sent		(int *perm, int *sigma, int n);
void		chase_exts			(Extremity_ctx *ctx, Extremity *ext, int *used);
void		print_chromosomes	(Extremity_ctx *ctx, int n);
void 		print_stack			(Stack_int *head);

// utils_read.c
int			read_exts			(char const *filename, Extremity_ctx *ctx, int *n);

// utils_stacks.c
void 		free_stack_node		(Stack_int *node);
void		free_stack			(Stack_int *head);
Stack_int 	*create_stack_node	(int nbr);
void 		push_stack			(Stack_int **head, int nbr);
Stack_int 	*pop_stack			(Stack_int **head);
int 		peek_stack			(Stack_int *head);


#endif
