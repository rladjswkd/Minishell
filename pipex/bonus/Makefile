NAME = pipex
CC = gcc -g
# CFLAGS = #-Wall -Wextra -Werror
RM = rm -rf
SRCS_DIR = srcs
UTILS_DIR = utils
INCLUDE = include
SRCS = $(addprefix $(SRCS_DIR)/, \
			main.c	\
	)
UTILS_SRCS = $(addprefix $(SRCS_DIR)/$(UTILS_DIR)/, \
			ft_strlen.c \
			ft_strjoin.c \
			ft_putstr.c \
			ft_split.c	\
			ft_strdup.c	\
			ft_strlcpy.c	\
			ft_strncmp.c	\
			ft_substr.c		\
			ft_strnstr.c	\
			utils.c	\
			get_next_line.c \
			get_next_line_utils.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_itoa.c \
	)
OBJS = $(SRCS:.c=.o) $(UTILS_SRCS:.c=.o)

%.o : %.c
	$(CC) -I ./$(INCLUDE)/ -c $^ -o $@
	# $(CC) $(CFLAGS) -I ./$(INCLUDE)/ -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $^ -o $@
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

