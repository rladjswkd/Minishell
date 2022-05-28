#for builtin
NAME = builtin
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm

SRCS = ./main.c	\
		./change_directory.c \
		./print_current_working_directory.c \
		./exit.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean:  clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
