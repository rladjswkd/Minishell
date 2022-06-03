NAME = PipeX
CC = gcc
CFLAGRS = #-Wall -Wextra -Werror
RM = rm
SRCS = ./main.c
OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGRS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all
