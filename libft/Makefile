
NAME = libft.a

SRCS = 	./ft_strlen.c 		\
 		./ft_bzero.c 		\
 		./ft_memset.c		\
		./ft_memcpy.c		\
		./ft_memccpy.c		\
		./ft_memmove.c		\
		./ft_calloc.c		\
		./ft_strdup.c		\
		./ft_memchr.c		\
		./ft_memcmp.c		\
		./ft_strlcpy.c		\
		./ft_strlcat.c		\
		./ft_strchr.c		\
		./ft_atoi.c			\
		./ft_isalpha.c		\
		./ft_isdigit.c		\
		./ft_isalnum.c		\
		./ft_isascii.c		\
		./ft_isprint.c		\
		./ft_substr.c		\
		./ft_toupper.c		\
		./ft_tolower.c		\
		./ft_split.c		\
		./ft_strrchr.c		\
		./ft_strncmp.c		\
		./ft_strnstr.c		\
		./ft_strtrim.c		\
		./ft_strjoin.c		\
		./ft_itoa.c			\
		./ft_strmapi.c		\
		./ft_putchar_fd.c	\
		./ft_putstr_fd.c	\
		./ft_putendl_fd.c	\
		./ft_putnbr_fd.c	\

OBJS = $(SRCS:.c=.o)

HEADERS = libft.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME):
	@echo "Compiling..."
	@$(CC) $(CFLAGS) -I $(HEADERS) $(SRCS)
	@ar rc $(NAME) $(OBJS)
	@echo "Success!"
	@ranlib $(NAME)

clean:
	@echo "Cleaning..."
	@/bin/rm -f $(OBJS)
	@echo "Success!"

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
