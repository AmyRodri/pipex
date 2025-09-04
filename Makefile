NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I libft/srcs/includes 

RM = rm -f
RUNLIB = -C libft

SRCS = mandatory/pipex.c 				\
		mandatory/pipex_utils.c 		\
		mandatory/exec.c				\

SRCSBONUS = bonus/pipex_bonus.c 		\
			bonus/pipex_fd.c			\
			bonus/exec_bonus.c 			\
			bonus/pipex_utils_bonus.c	\
			bonus/here_d_utils_bonus.c	\

OBJS = $(SRCS:.c=.o)
OBJSBONUS = $(SRCSBONUS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	$(MAKE) $(RUNLIB)

bonus: $(OBJSBONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJSBONUS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS) $(OBJSBONUS)
	$(MAKE) clean $(RUNLIB)

fclean: clean
	$(RM) $(NAME) $(LIBFT)
	$(MAKE) fclean $(RUNLIB)

re: fclean all

.PHONY: all clean fclean re
