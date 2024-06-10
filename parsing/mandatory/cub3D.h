/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:33:04 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/10 17:33:05 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>

# define PIXS_BASE 12

# define ERROR "Error\n"
# define INV_ENT_NUM "Invalid number of player, start instance\n"

# define NAME "so_long"
# define WIN_L 1000
# define WIN_H 600

# define CUB ".cub"
# define XPM ".xpm"
# define WALL '1'
# define GROUND '0'

# define FLOOR 'F'
# define CEILING 'C'

# define SOUTH "SO"
# define WEST "WE"
# define NORTH "NO"
# define EAST "EA"

# define PS 'S'
# define PW 'W'
# define PN 'N'
# define PE 'E'

# define NB_DIR 4
# define NB_SPRITES 4

typedef struct s_dep
{
	int	x;
	int	y;
}	t_dep;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	**map_cp;
	char	**map;
}	t_vars;

typedef struct s_pos
{
	size_t	x;
	size_t	y;
}	t_pos;

typedef struct s_game
{
	t_vars	vars;

	void	*wall_img[NB_DIR];
	char	*wall_files[NB_DIR];

	int		floor[3];
	int		ceil[3];
}	t_game;

t_game	cub3d(char *file);

//		map parsing
int		check_open(char **map);
void	flood_fill(char **map, size_t pos_x, size_t pos_y);
int		check_path(char **map);
int		check_map(char **map);

//		map utils
size_t	get_nb_line(char *file);
char	**get_map(char *file);
t_pos	get_coord(char **map, char c);
t_pos	get_suiv(char **map, t_pos ind, char c);
int		get_colour(int *tab, char *line);
void	get_file(t_game *game, char *file);

//		init
void	init_game(t_game *game, char *file);

//		data
char	*make_file(char *str1, char *str2, char *str3, char *str4);
void	*make_data(t_game *game, char *file, t_dep s);
void	make_data_map(t_game *game);

//		game utils
int		open_fd(char *file);
size_t	get_nb_inst(char **map, char c);
int		ft_close(int val_exit);

//		libft
char	*ft_strdup(char *src);
size_t	ft_strlen(char const *str);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
// pour améliorer le parsing
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);
size_t	ft_strlcat(char *dest, char const *src, size_t n);
size_t	ft_strlcpy(char *dest, char const *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *str, char const *sep);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);;
#endif
