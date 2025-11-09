
#include "genome.h"

void	free_ext(Extremity *ext)
{
	xfree(ext, sizeof(Extremity));
}

void 	free_array_exts(Extremity **exts, int n)
{
	int i;

	i = 0;
	while (i < n * 2)
	{
		if (exts[i])
			free_ext(exts[i]);
		i++;
	}
	xfree(exts, sizeof(Extremity *) * (n * 2));
}

void 	print_array_exts(Extremity **exts, int n)
{
	int i;
	int id1, sign1;
	int id2, sign2;
	Extremity *ext1, *ext2;

	i = 0;
	while (i < n)
	{
		ext1 = exts[i * 2];
		ext2 = exts[i * 2 + 1];
		id1 = ext1->id;
		id2 = ext2->id;
		sign1 = ext1->sign;
		sign2 = ext2->sign;
		printf("%d->", id1 * sign1);
		if (ext1->reality)
			printf("%d\n", ext1->reality->id * ext1->reality->sign);
		else
			printf("None\n");
		printf("%d->", id2 * sign2);
		if (ext2->reality)
			printf("%d\n", ext2->reality->id * ext2->reality->sign);
		else
			printf("None\n");
		i++;
	}
	printf("\n");
}

Extremity *create_ext(int id, int sign)
{
	Extremity *ext;

	ext = (Extremity *)xmalloc(sizeof(Extremity) * 1);
	if (!ext)
		return (NULL);
	ext->id = id;
	ext->sign = sign;
	ext->reality = NULL;
	ext->desire = NULL;
	return (ext);
}
