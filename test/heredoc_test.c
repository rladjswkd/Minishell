#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	heredoc test
	- readline으로 입력을 받는다.
	- 
*/
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

static size_t	ft_strlen(const char *str)
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
		if (file_open(FILE_READ, file_name) < 0)
			break ;
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

static int	get_readline(char *file_name, int tmp_file_fd, char *heredoc_word)
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

static int	create_heredoc_tmpfile(char	*file_name)
{
	int		tmp_file_fd;

	file_name = check_tmp_file();
	if (file_name == NULL)
		return (-1);
	tmp_file_fd = redirection(HERE_DOC, file_name);
	if (tmp_file_fd < 0)
	{
		safe_free(&file_name);
		return (-1);
	}
	return (tmp_file_fd);
}

/*
	우선입력만 받았으며 임시파일에 저장한 상태이다.
	임사
*/
static int	tmp_to_stdin(char *file_name)
{
	int	tmp_file_fd;

	tmp_file_fd = file_open(FILE_READ, file_name);
	dup2(tmp_file_fd, STDIN_FILENO);
	unlink(file_name);//wsl에서는 문제 발생
	close(tmp_file_fd);
	safe_free(&file_name);
}

static int	heredoc_rountine(char *heredoc_word)
{
	int		tmp_file_fd;
	char	*file_name;

	tmp_file_fd = create_heredoc_tmpfile(file_name);
	if (tmp_file_fd < 0)
		return (tmp_file_fd);
	get_readline(*file_name, tmp_file_fd, heredoc_word);
	tmp_to_stdin(file_name);
}

/*
	- argv로 heredoc을 입력받는다.
		'<<'입력은 생략하며 heredoc word만 받는다.
	- tmp file을 만든다.
	- heredoc word와 일치할떄까지 값을 입력받아서 임시파일에 추가한다.
	- heredoc word와 일치하는 입력값을 받으면 입력을 더이상 받지 않으며 tmp file fd 또한 close한다.
*/

// 1개의 heredoc만 받는다는 가정
int	main(int argc, char **argv)
{
	char	*heredoc_word;

	if (argc < 2)
		return (1);
	heredoc_word = argv[1];
	heredoc_rountine(heredoc_word);
	return (0);
}
