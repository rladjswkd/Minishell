#include "utils.h"

int	ft_strchr(char *s, int c)
{
	size_t	idx;

	if (s == NULL)
		return (-1);
	idx = 0;
	while (s[idx])
	{
		if (s[idx] == (char)c)
			return (idx);
		idx++;
	}
	if (s[idx] == (char)c)
		return (idx);
	return (-1);
}
