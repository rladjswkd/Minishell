#for builtin
NAME = builtin
CC = gcc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = ./main.c	\
		./change_directory.c \
		./print_current_working_directory.c \
		./exit.c \
		./environment_variable.c \
		./echo.c \
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
