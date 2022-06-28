NAME = minishell
CC = gcc
#CFLAGS = -Wall -Wextra -Werror
LDLIBS = -lreadline
RM = rm -rf
INCLUDE = include
SRCS_DIR = srcs
DATA_STRUCT_DIR = data_structure
LINKED_LIST_DIR = linked_list
UTILS_DIR = utils
TOKEN_DIR = token
LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include
SRCS = $(addprefix $(SRCS_DIR)/, \
			minishell.c	\
			init.c	\
	)
UTIL_SRCS = $(addprefix $(SRCS_DIR)/$(UTILS_DIR)/, \
			ft_strndup.c	\
			ft_strchr.c	\
			ft_strlen.c \
	)
LINKED_SRCS = $(addprefix $(SRCS_DIR)/$(DATA_STRUCT_DIR)/$(LINKED_LIST_DIR)/, \
			env_list.c	\
	)

OBJS = $(SRCS:.c=.o)
UTIL_OBJS = $(UTIL_SRCS:.c=.o)
LINKED_OBJS  = $(LINKED_SRCS:.c=.o)

%.o : %.c
	$(CC) $(COMFILE_FLAGS) -I ./$(INCLUDE)/ -c $^ -o $@
# $(CC) $(CFLAGS) -I ./$(INCLUDE)/ -c $^ -o $@

$(NAME) : $(OBJS) $(UTIL_OBJS) $(LINKED_OBJS)
	$(CC) $(LINKING_FLAGS) $^ -o $@
# $(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS) $(UTIL_OBJS) $(LINKED_OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

 .PHONY : all clean fclean re
