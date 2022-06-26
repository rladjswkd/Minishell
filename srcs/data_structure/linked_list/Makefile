#for linked_list
NAME = linked_list_simple
CC = gcc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = ./linked_list_simple.c	\
		./ft_strncmp.c \
		./utils.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) -c $^ -o $@
	# $(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $^ -o $@
	# $(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean:  clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
