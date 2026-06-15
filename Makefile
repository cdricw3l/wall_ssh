NAME=wall_ssh
CC=gcc
CFLAGS= -Wall -Wextra -Werror
SRCS= 	ft_split_clean.c \
		ft_strjoin.c \
		ft_strlcpy.c \
		ft_strlen.c \
		wall_ssh.c

SRCS_OBJ= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS_OBJ)
	$(CC) $(CFLAGS) $(SRCS_OBJ) -o $(NAME)

clean:
	rm -rf $(SRCS_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all