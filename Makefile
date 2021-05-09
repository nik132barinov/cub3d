SRCS			=	main.c				\
					map_file_parse.c	\
					map_print.c			\
					map_get_set.c		\
					map_parse.c			\
					render.c			\
					free_mlx_data.c		\
					bitmap.c			\
					event_handler.c		\
					cub3d.c				\
					move.c				\
					displacement.c		\
					free_data.c			\
					validate.c			\
					read_textures.c		\
					read_colors.c		\
					valid_read_textures.c \
					read_map.c				\
					read_resolution.c		\
					create_view.c			\
					xy_intersect.c			\
					ray_0_PI2_intersect.c	\
					raycast.c				\
					quant_view.c			\
					map_parse_utils.c		\
					libft/ft_atoi.c			\
					libft/ft_isdigit.c		\
					libft/ft_strlen.c		\
					libft/ft_strncmp.c		\

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re