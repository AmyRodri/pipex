NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I libft/srcs/includes -I includes

RM = rm -f
RUNLIB = -C libft

SRCS = srcs/pipex.c 				\
			srcs/fd_utils.c			\
			srcs/exec.c 			\
			srcs/utils.c			\
			srcs/here_doc.c			\
			srcs/checks.c			\
			srcs/ft_split_quotes.c	\

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	$(MAKE) $(RUNLIB)

clean:
	$(RM) $(OBJS)
	$(MAKE) fclean $(RUNLIB)

fclean: clean
	$(RM) $(NAME) $(LIBFT)
	$(MAKE) fclean $(RUNLIB)

re: fclean all

.PHONY: all clean fclean re
