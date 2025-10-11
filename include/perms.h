#ifndef PERMS_H
# define PERMS_H

# include "../include/lib.h"

// gen_perms.c
int			*gen_perm			(int start, int end, int *n);
int 		*gen_unsigned_perm	(int n);
void		*add_extremity		(int *perm, int *n);
void		*add_pairs			(int *perm, int *n);

// shuffle_perms.c
void		shuffle_perm	(int *perm, int n);

#endif
