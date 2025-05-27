#include "lib.h"

void 	free_array_char(char **ss, int n)
{
	int i;

	i = 0;
	while (i < n && ss[i])
	{
		xfree(ss[i], sizeof(char) * (strlen(ss[i]) + 1));
		i++;
	}
	xfree(ss, sizeof(char *) * n);
}

int 	count_digit(unsigned int number)
{
	if (number < 10)
	{
		return 1;
	}
	return (count_digit(number / 10) + 1);
}