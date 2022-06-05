NAME = pipex
CC = gcc
# CFLAGS = #-Wall -Wextra -Werror
RM = rm -rf
SRCS = ./main.c \
		./ft_split.c \
		./ft_strdup.c \
		./ft_strncmp.c \
		./ft_substr.c \
		./ft_strlcpy.c \
		./utils.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) -c $^ -o $@
# $(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $^ -o $@
#$(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

 .PHONY : all clean fclean re
