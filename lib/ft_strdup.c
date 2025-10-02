#include "lib.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int	len, i;

	len = 0;
	while (s[len])
		len++;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
