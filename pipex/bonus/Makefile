NAME = pipex
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
RM = rm -rf
SRCS_DIR = srcs
INCLUDE = include
SRCS = $(addprefix $(SRCS_DIR)/, \
			main.c	\
			ft_split.c	\
			ft_strdup.c	\
			ft_strlcpy.c	\
			ft_strncmp.c	\
			ft_substr.c		\
			ft_strnstr.c	\
			utils.c	\
			get_next_line.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_itoa.c \
	)
OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -I ./$(INCLUDE)/ -c $^ -o $@

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

 .PHONY : all clean fclean re
