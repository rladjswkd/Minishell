#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

size_t  ft_strlen(char const *str)
{
	size_t  len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	max_nonnegative(char const *s1, char const *s2)
{
	size_t	s1_size;
	size_t	s2_size;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (s1_size > s2_size)
		return (s1_size);
	return (s2_size);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (i++ < n)
	{
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2)
		{
			if (c1 < c2)
				return (-1);
			else
				return (1);
		}
		if (!c1)
			break ;
	}
	return (0);
}

int	check_tmp_file_name(char *file_name)
{
	DIR				*dir_ptr = NULL;
	struct dirent	*file    = NULL;
	char			buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	if((dir_ptr = opendir(buf)) == NULL)
		return -1;
	while((file = readdir(dir_ptr)) != NULL) 
	{
		if (ft_strncmp(file_name, file->d_name, \
						max_nonnegative(file_name, file->d_name)) == 0)
			return (1);
	}
	closedir(dir_ptr);
	return (0);
}

int main(int argc, char **argv)
{
	char    *file_name;

	file_name = argv[1];
	if (check_tmp_file_name(file_name))
		printf("exist.\n");
	else
		printf("not exist.\n");
	return 0;
}
