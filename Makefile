NAME = minishell
CC = cc -g
#CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -g
LDLIBS = -lreadline
RM = rm -f
INCLUDE = include
SRCS_DIR = srcs
DATA_STRUCT_DIR = data_structure
LINKED_LIST_DIR = linked_list
BUILTIN_DIR = builtin
UTILS_DIR = utils
TOKEN_DIR = token
LEXER_DIR = lexer
PARSER_DIR = parser
EXECUTE_DIR = execute
REDIRECT_DIR = redirect
HEREDOC_DIR = heredoc
PIPE_DIR = pipe
LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include
SRCS = $(addprefix $(SRCS_DIR)/, \
			minishell.c	\
			init.c	\
)

LINKED_SRCS = $(addprefix $(SRCS_DIR)/$(DATA_STRUCT_DIR)/$(LINKED_LIST_DIR)/, \
			env_list.c	\
			env_list_remove.c \
			plain_linked_list.c \
)

LEXTER_SRCS = $(addprefix $(SRCS_DIR)/$(LEXER_DIR)/, \
			lexer.c	\
)

EXECUTE_SRCS = $(addprefix $(SRCS_DIR)/$(EXECUTE_DIR)/, \
		execute.c	\
		execute_scmd.c \
		execute_builtin.c \
)

REDIRECT_SRCS = $(addprefix $(SRCS_DIR)/$(REDIRECT_DIR)/, \
		redirect.c	\
		redirect_utils.c \
)

HEREDOC_SRCS = $(addprefix $(SRCS_DIR)/$(HEREDOC_DIR)/, \
		heredoc.c	\
		heredoc_utils.c \
) 

PIPE_SRCS = $(addprefix $(SRCS_DIR)/$(PIPE_DIR)/, \
		pipe.c	\
		pipe_utils.c \
)

BUILTIN_SRCS = $(addprefix $(SRCS_DIR)/$(BUILTIN_DIR)/, \
			cd.c	\
			pwd.c	\
			echo.c	\
			env.c	\
			exit.c	\
			export.c	\
			unset.c	\
)

UTIL_SRCS = $(addprefix $(SRCS_DIR)/$(UTILS_DIR)/, \
			ft_strndup.c	\
			ft_strjoin.c	\
			ft_strdup.c	\
			ft_strchr.c	\
			ft_strnstr.c \
			ft_strlen.c	\
			ft_split.c	\
			ft_strlcat.c	\
			ft_strlcpy.c	\
			ft_putstr_fd.c	\
			ft_strncmp.c	\
			ft_substr.c	\
			ft_is_alpha.c	\
			ft_is_digit.c	\
			ft_error.c	\
			exit_status.c \
			check_valid_name.c	\
			utils.c	\
)

OBJS = $(SRCS:.c=.o)
LEXTER_OBJS = $(LEXTER_SRCS:.c=.o)
EXECUTE_OBJS = $(EXECUTE_SRCS:.c=.o)
REDIRECT_OBJS = $(REDIRECT_SRCS:.c=.o)
HEREDOC_OBJS = $(HEREDOC_SRCS:.c=.o)
PIPE_OBJS = $(PIPE_SRCS:.c=.o)
BUILTIN_OBJS  = $(BUILTIN_SRCS:.c=.o)
LINKED_OBJS  = $(LINKED_SRCS:.c=.o)
UTIL_OBJS = $(UTIL_SRCS:.c=.o)

%.o : %.c
	$(CC) -I ./$(INCLUDE)/ -c $^ -o $@ $(LDLIBS)

# $(CC) -I ./$(INCLUDE)/ -c $^ -o $@ $(LDLIBS)

# $(CC) $(COMFILE_FLAGS) -I ./$(INCLUDE)/ -c $^ -o $@
# $(CC) $(CFLAGS) -I ./$(INCLUDE)/ -c $^ -o $@

$(NAME) : $(OBJS) $(UTIL_OBJS) $(LINKED_OBJS) $(REDIRECT_OBJS) $(HEREDOC_OBJS) $(PIPE_OBJS) $(BUILTIN_OBJS) $(EXECUTE_OBJS) $(LEXTER_OBJS)
	$(CC) $^ -o $@ $(LDLIBS)

# $(CC) $(LINKING_FLAGS) $^ -o $@
# $(CC) $^ -o $@ $(LDLIBS)
# $(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS) $(UTIL_OBJS) $(LINKED_OBJS) $(REDIRECT_OBJS) $(HEREDOC_OBJS) $(PIPE_OBJS)  $(BUILTIN_OBJS) $(EXECUTE_OBJS) $(LEXTER_OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

 .PHONY : all clean fclean re
