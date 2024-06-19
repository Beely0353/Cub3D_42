RED		=	\033[31mdata->ndata->ray.wall_x
GRE		=	\033[32m
BLU		=	\033[36m
YEL		=	\033[33m
EOC		=	\033[0m
BEI		=	\033[38;5;223m

DEF		=	\033[0m
BOLD	=	\033[1m
CUR		=	\033[3m
UL		=	\033[4m
UP		=	\033[A

NAME		=	cub3D

SOURCES		=	./src
INCLUDES	=	./include
OBJECTS		=	./bin

SRCS			=	cub3d.c cub3d_init.c cub3d_data.c \
					$(addprefix utils/, ft_strfd.c ft_strutils.c get_next_line_bonus.c utils.c str_utils.c) \
					$(addprefix parsing/, cub3d_game_utils.c cub3d_map_parsing.c cub3d_map_utils.c parse_ray.c) \
					$(addprefix raycasting/, raycasting.c raycasting2.c raycasting_utils.c) move.c \


OBJS		=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

MLX_DIR 	=	./minilibx-linux/
CFLAGS		=	-Wall -Wextra -Werror -g -I$(MLX_DIR) -Iinclude -lm
CC			=	gcc
CINCLUDES	=	-I ${INCLUDES}

ifeq ($(shell uname), Linux)
	LIBMLX_DIR	= lib/libmlx/linux
else
	LIBMLX_DIR	= lib/libmlx/macos
endif
# ---------------------------------------------------------------------------- #

SRCS_COUNT = 0
SRCS_TOT = ${shell find ./src/ -type f -name '*.c' | wc -l}
SRCS_PRCT = ${shell expr 100 \* ${SRCS_COUNT} / ${SRCS_TOT}}
BAR =  ${shell expr 23 \* ${SRCS_COUNT} / ${SRCS_TOT}}

${OBJECTS}/%.o: ${SOURCES}/%.c
	@${eval SRCS_COUNT = ${shell expr ${SRCS_COUNT} + 1}}
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}
	@echo ""
	@echo "\r\033[K -> Compilation de ""$(YEL)${notdir $<}$(EOC). ⏳"
	@printf "   ${BEI}[%-23.${BAR}s] [%d/%d (%d%%)]${DEF}" "***********************" ${SRCS_COUNT} ${SRCS_TOT} ${SRCS_PRCT}
	@echo "${UP}${UP}${UP}"

all: start ${NAME}

start:
	@if [ ! -e "bin" ]; then \
		echo "🚀 Début de la compilation de $(BLU)${NAME} 🚀$(EOC)"; \
	else \
		echo "make: Nothing to be done for \`all'."; \
	fi

${NAME}: ${OBJS}
	@clear
	@echo "$(GRE)✅ Compilation terminée.$(EOC)"
	@$(CC) -L$(MLX_DIR) -o $@ $^ -lmlx $(CFLAGS) -lX11 -lXext

clean:
	@echo "🗑  $(RED)Supression des fichiers binaires (.o).$(EOC) 🗑"
	@rm -rf ${OBJECTS}

fclean: clean
	@echo "🗑  $(RED)Supression des executables et librairies.$(EOC) 🗑"
	@rm -f ${NAME}
	@rm -rf includes/readline
	@clear

re: fclean all

fcleanr: clean
	@echo "🗑  $(RED)Supression des executables et librairies.$(EOC) 🗑"
	@rm -f ${NAME}
	@clear

rer: fcleanr all

.PHONY:	all clean fclean re
