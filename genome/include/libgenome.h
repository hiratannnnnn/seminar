#ifndef LIBGENOME_H
# define LIBGENOME_H

# include "../../include/lib.h"
# include "../../include/perms.h"

// conditions.c
int 		can_rev					(int x, int y, int size);
int 		can_revrev				(int x, int y, int z, int size);
int 		can_transpose			(int x, int y, int z, int size);
int 		can_block_interchange	(int x, int y, int z, int w, int size);

// breakpoint.c
int 		count_breakpoints		(int *perm, int n);

// reversal.c
void		rev						(int *perm, int x, int y, int n);
void		revrev					(int *perm, int x, int y, int z, int n);

// transposition.c
void		transpose				(int *perm, int x, int y, int z, int n);
void		block_interchange		(int *perm, int x, int y, int z, int w, int n);

// // insertion.c
// void 		insert					(int *perm, int x, int *T, int n);

// // deletion.c
// void		delete					(int *perm, int x, int y, int n);

// double-cut-and-join
// block-interchange

#endif
