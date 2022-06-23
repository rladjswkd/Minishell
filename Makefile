NAME = minishell
CC = gcc
LDLIBS = -lreadline
RM = rm -rf
SRCS_DIR = srcs
UTILS_DIR = utils
INCLUDE = include
SRCS = $(addprefix $(SRCS_DIR)/, \
			minishell.c	\
	)

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) -I ./$(INCLUDE)/ -c $^ -o $@ $(LDLIBS)
# $(CC) $(CFLAGS) -I ./$(INCLUDE)/ -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $^ -o $@ $(LDLIBS) 
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