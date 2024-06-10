SRCS			=	get_next_line_bonus.c		\
					cub3D_game_utils.c		cub3D_map_parsing.c		\
					cub3D_map_utils.c		\
					cub3D_data.c			cub3D_init.c				\
					ft_putchar_fd.c		ft_putstr_fd.c	\
					ft_strdup.c			ft_strjoin.c	\
					ft_strlcpy.c			ft_strlen.c	\
					ft_strncmp.c			\
					ft_substr.c			cub3D.c

OBJS			=	$(SRCS:.c=.o)

CC			=	gcc
RM			=	rm -f
PATH_MLX		=	../minilibx/
CFLAGS			=	-I. 
#-Wall -Wextra -Werror -I.
MLXFLAGS		=	-L$(PATH_MLX) -lmlx -lXext -lX11

NAME			=	../cub3D

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(OBJS) $(CFLAGS) $(MLXFLAGS) -o $(NAME)
				@printf $$'\033[32mcompilation done\033[0m\n'

clean:
				@$(RM) $(OBJS)
				@printf $$'\033[31mobject files removed\033[0m\n'

fclean:			clean
				@$(RM) $(NAME)
				@printf $$'\033[31mlibft cleaned\033[0m\n'

re:				fclean $(NAME)

%.o :%.c
				@$(CC) $(CFLAGS) -c $< -o $@
				@printf $$'\033[32mcompiling $<                \033[0m\r'

.PHONY:			all clean fclean re
