#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/errno.h>
#include <strings.h>

/*
	heredoc test
	- readline으로 입력을 받는다.
	- 
*/

typedef struct s_list
{
	void			*node;
	struct s_list	*next;
}				t_list;

typedef struct s_heredoc_node
{
	int		fd;
}				t_heredoc_node;

typedef enum e_redirection_flag
{
	NONE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
}				t_redirection_flag;

typedef enum e_file_flag
{
	FILE_READ,
	FILE_WRITE,
	FILE_APPEND,
	FILE_RDWR,
	FILE_WRONLY,
}				t_file_flag;

typedef enum e_flag
{
	ERROR = -1,
	SUCCESS = 0,
	FAIL = 1,
}				t_e_flag;

typedef enum e_pipe_flag
{
	READ_END,
	WRITE_END,
}			t_pipe_flag;

typedef struct s_execute_info
{
	char				*cmd;
	char				**envp;
	char				pipe_fd[2];
	t_redirection_flag	redirection_flag;
	char				*heredoc_word;
	char				*file_name;
}				t_execute_info;

size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
static int	get_readline(char *file_name, int tmp_file_fd, char *heredoc_word);

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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	org_dstsize;

	i = ft_strlen(dst);
	j = 0;
	org_dstsize = i;
	while (src[j] != '\0' && (org_dstsize + j + 1 < dstsize))
		dst[i++] = src[j++];
	if (org_dstsize < dstsize)
		dst[i] = '\0';
	while (src[j] != '\0')
		j++;
	if (dstsize < org_dstsize)
		return (j + dstsize);
	else
		return (j + org_dstsize);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (src[i] != '\0')
		i++;
	if (dstsize == 0)
		return (i);
	while ((k < dstsize - 1) && src[k])
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	return (i);
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

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	idx;
	size_t	s1_size;

	if (s1 == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (s1_size + 1));
	if (dest == NULL)
		return (NULL);
	idx = 0;
	while (s1[idx])
	{
		dest[idx] = s1[idx];
		idx++;
	}
	dest[idx] = 0;
	return (dest);
}

size_t	count_digits(int n)
{
	size_t	expo;

	expo = 0;
	if (n < 0)
	{
		n *= -1;
		expo++;
	}
	while (n)
	{
		expo++;
		n /= 10;
	}
	return (expo);
}

char	*ft_itoa(int n)
{
	size_t	digits;
	char	*to_be_s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	digits = count_digits(n);
	to_be_s = (char *)malloc(sizeof(char) * (digits + 1));
	if (!to_be_s)
		return (0);
	if (n < 0)
	{
		n = -n;
		to_be_s[0] = '-';
	}
	to_be_s[digits] = '\0';
	digits--;
	while (n)
	{
		to_be_s[digits] = (n % 10) + '0';
		digits--;
		n /= 10;
	}
	return (to_be_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	dstsize;

	dstsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *)malloc(sizeof(char) * (dstsize));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, dstsize);
	return (dst);
}

static void	safe_free(char	**char_pptr)
{
	free(*char_pptr);
	*char_pptr = NULL;
}

int	file_open(t_file_flag file_flag, char *file_name)
{
	int	file_fd;

	file_fd = -1;
	if (file_flag == FILE_READ)
		file_fd = open(file_name, O_RDONLY, 0644);
	else if (file_flag == FILE_WRITE)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (file_flag == FILE_APPEND)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (file_flag == FILE_RDWR)
		file_fd = open(file_name, O_CREAT | O_RDWR, 0644);
	return (file_fd);
}

int	redirection(t_redirection_flag redirection_flag, char *file_name)
{
	int	file_fd;

	file_fd = -1;
	if (redirection_flag == INPUT)
		file_fd = file_open(FILE_READ, file_name);
	else if (redirection_flag == OUTPUT)
		file_fd = file_open(FILE_READ, file_name);
	else if (redirection_flag == HERE_DOC)
		file_fd = file_open(FILE_RDWR, file_name);
	else if (redirection_flag == APPEND)
		file_fd = file_open(FILE_APPEND, file_name);
	else
		write(2, &"unknown redirection_flag\n.", \
				ft_strlen("unknown redirection_flag\n."));
	return (file_fd);
}

static char	*check_tmp_file(void)
{
	char	*file_name;
	char	*itoa_num;
	int		num;
	int		tmp_fd;

	num = 0;
	while (1)
	{
		itoa_num = ft_itoa(num);
		if (itoa_num == NULL)
			return (NULL);
		file_name = ft_strjoin(".heredoc_tmpfile_", itoa_num);
		safe_free(&itoa_num);
		if (file_name == NULL)
			return (NULL);
		tmp_fd = file_open(FILE_READ, file_name);
		if (tmp_fd < 0)
			break ;
		close(tmp_fd);
		safe_free(&file_name);
		num++;
	}
	return (file_name);
}

static void	input_to_tmpfile(char *file_name, int tmp_file_fd, char *heredoc_word)
{
	char	*read_str;

	while (1)
	{
		read_str = readline("$>");
		if (ft_strncmp(read_str, heredoc_word, \
			max_nonnegative(read_str, heredoc_word)) == 0)
		{
			safe_free(&read_str);
			break ;
		}
		if (write(tmp_file_fd, read_str, ft_strlen(read_str)) < 0)
			exit(1);
		safe_free(&read_str);
	}
	close(tmp_file_fd);
}

static int	free_and_close(char *file_name, int tmp_file_fd, char *read_str)
{
	unlink(file_name);
	safe_free(&file_name);
	safe_free(&read_str);
	if (close(tmp_file_fd) < 0)
		return (-1);
	return (1);
	//계속 return시킬 것 아니라면 exit한다.
}

static int	ft_putendl_fd(int fd, char *str)
{
	if (write(fd, str, ft_strlen(str) < 0))
		// || write(fd, &"\n", 1) < 0)
		return (-1);
	return (1);
}

static int	get_readline(char *file_name, int tmp_file_fd, char *heredoc_word)
{
	char	*read_str;
	char	*with_newline;

	while (1)
	{
		read_str = readline("$>");
		// printf("read_str : %zu\n", ft_strlen(read_str));
		if (ft_strncmp(read_str, heredoc_word, \
			max_nonnegative(read_str, heredoc_word)) == 0)
		{
			safe_free(&read_str);
			break ;
		}
		with_newline = ft_strjoin(read_str, "\n");
		if (with_newline == NULL)
		{
			safe_free(&read_str);
			return (-1);
		}
		safe_free(&read_str);
		if (write(tmp_file_fd, with_newline, ft_strlen(with_newline)) < 0)
			return (free_and_close(file_name, tmp_file_fd, read_str));
		safe_free(&with_newline);
	}
	close(tmp_file_fd);
	return (1);
}

static int	create_heredoc_tmpfile(char	**file_name)
{
	int		tmp_file_fd;

	*file_name = check_tmp_file();
	if (*file_name == NULL)
		return (-1);
	tmp_file_fd = redirection(HERE_DOC, *file_name);
	if (tmp_file_fd < 0)
	{
		safe_free(file_name);
		return (-1);
	}
	return (tmp_file_fd);
}

/*
	우선입력만 받았으며 임시파일에 저장한 상태이다.
	임사
*/
static int	get_tmp_file_fd(char *file_name)
{
	int	open_fd;

	open_fd = file_open(FILE_READ, file_name);
	printf("open_fd : %d\n", open_fd);
	if (open_fd < 0)
		return (-1);
	if (unlink(file_name) < 0)//wsl에서는 문제 발생
		return (-1);
	safe_free(&file_name);
	return (open_fd);
}

static int	heredoc_routine(char *heredoc_word)
{
	int		tmp_file_fd;
	char	*file_name;
	char	buf[4242 + 1];

	tmp_file_fd = create_heredoc_tmpfile(&file_name);
	if (tmp_file_fd < 0)
		return (-1);
	if (get_readline(file_name, tmp_file_fd, heredoc_word) < 0)
		return (-1);
	tmp_file_fd = get_tmp_file_fd(file_name);
	if (tmp_file_fd < 0)
		return (-1);
	return (tmp_file_fd);
}

/*
	- argv로 heredoc을 입력받는다.
		'<<'입력은 생략하며 heredoc word만 받는다.
	- tmp file을 만든다.
	- heredoc word와 일치할떄까지 값을 입력받아서 임시파일에 추가한다.
	- heredoc word와 일치하는 입력값을 받으면 입력을 더이상 받지 않으며 tmp file fd 또한 close한다.
*/

/*
	- 여러개의 fd를 연결리스트에 담아서 처리한다.
		fd를 읽어와서 일괄적으로 출력한다.

typedef struct s_list
{
	void			*node;
	struct s_list	*next;
}				t_list;

p 
*/

t_list	*create_list()
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	new_list->node = NULL;
	new_list->next = NULL;
	return (new_list);
}

static void	free_node(t_list **node)
{
	free(*node);
	*node = NULL;
}

static void	free_list(t_list **list)
{
	t_list	*cur_node;
	t_list	*removed_node;

	if (list == NULL || *list == NULL)
		return ;
	cur_node = *list;
	while (cur_node)
	{
		removed_node = cur_node;
		cur_node = cur_node->next;
		free_node(&removed_node);
	}
}

/*
	실제사용할때 어떻게 쓰일것으로 예상되는가?
	어떻게 쓰이게 주는게 에러 발생가능성이 적고 유지보수하기 편리한가?
*/
int	heredoc_fd_to_list(t_list *list, int fd)
{
	t_list			*cur_node;
	t_heredoc_node	*heredoc_node;

	if (fd < 0)
	{
		free_list(&list);
		return (-1);
	}
	while (list->next)
		list = list->next;
	list->next = create_list();
	cur_node = list->next;
	if (cur_node == NULL)
	{
		free_list(&list);
		return (-1);
	}
	heredoc_node = (t_heredoc_node *)malloc(sizeof(t_heredoc_node));
	if (heredoc_node == NULL)
	{
		free_list(&list);
		return (-1);
	}
	heredoc_node->fd = fd;
	cur_node->node = (t_heredoc_node *)heredoc_node;
	return (0);
}

static void	print_heredoc_list(t_list *list)
{
	ssize_t			len;
	t_heredoc_node	*heredoc_node;
	char			buf[4242];

	list = list->next;
	while (list)
	{
		heredoc_node = (t_heredoc_node *)list->node;
		printf("\n=========================\n");
		printf("heredoc_node->fd : %d\n", heredoc_node->fd);
		len = read(heredoc_node->fd, buf, 4242);
		buf[len] = '\0';
		printf("read size : %ld\n", len);
		printf("error code : %s\n", strerror(errno));
		printf("heredoc : \n%s", buf);
		list = list->next;
	}
}


/*
- 제약조건
	- header node가 없다.
	 	- 중간에 값을 추가하다가 error가 나는 경우 시작위치를 알 수 없다.
		- 다음 노드로 이을떄 next에 할당해야한다.
	- 첫 노드로 항상 비워두고 시작노드로 쓴다.

*/


/*
	- 현재 list에 node에 담고자하는 구조체를 캐스팅해서 가리키게한다.
	- next와  
*/
static void	init_list(t_list *list)
{
	list->next = NULL;
	list->node = NULL;
}

int	main(int argc, char **argv)
{
	char			*heredoc_word;
	int				heredoc_fd;
	int				idx;
	t_list			common_list;
	t_list			*cur_node;

	// printf("common_list : %p\n", &common_list);
	// printf("common_list.next : %p\n", &(common_list.next));
	// printf("cur_node : %p\n", cur_node);
	// init_list(&common_list);
	if (argc < 2)
		return (1);
	idx = 1;
	create_heredoc_tmpfile(&argv[1]);
	printf("error code : %s\n", strerror(errno));
	// while (idx < argc)
	// {
	// 	if (heredoc_fd_to_list(&common_list, heredoc_routine(argv[idx])) < 0)
	// 		return (ENOMEM);
	// 	idx++;
	// }
	// print_heredoc_list(&common_list);
	return (0);
}
