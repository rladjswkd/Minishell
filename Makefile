NAME = minishell
CC = gcc
#CFLAGS = -Wall -Wextra -Werror
LDLIBS = -lreadline
RM = rm -rf
INCLUDE = include
SRCS_DIR = srcs
UTILS_DIR = utils
TOKEN_DIR = token
LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include
SRCS = $(addprefix $(SRCS_DIR)/, \
			minishell.c	\
	)

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(COMFILE_FLAGS) -I ./$(INCLUDE)/ -c $^ -o $@
# $(CC) $(CFLAGS) -I ./$(INCLUDE)/ -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $(LINKING_FLAGS) $^ -o $@
# $(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

 .PHONY : all clean fclean re
