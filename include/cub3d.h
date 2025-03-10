/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:53:19 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/20 18:55:01 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <X11/keysym.h>
# include <time.h>
# include <math.h>
# include <stddef.h>
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1500
# endif
# define OPEN_MAX 500

# define NAME "cub3d"

# define ERROR "Error\n"

# define HEIGHT 600
# define WIDTH  1000

# define CUB ".cub"
# define XPM ".xpm"

# define FLOOR 'F'
# define CEILING 'C'
# define SOUTH "SO"
# define WEST "WE"
# define NORTH "NO"
# define EAST "EA"

# define WALL '1'
# define GROUND '0'
# define PS 'S'
# define PW 'W'
# define PN 'N'
# define PE 'E'

# define NB_DIR 4

# define KEY_Z 119
# define KEY_Q 97
# define KEY_S 115
# define KEY_D 100
# define KEY_N 110
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_ESC 65307

# define PI 3.1415926535
# define MOVEMENT 0.06
# define ROTATION 0.05

typedef struct s_pos
{
	size_t	x;
	size_t	y;
}	t_pos;

typedef struct s_img
{
	void	*img;
	char	*addr;
	char	*file;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		width;
	int		height;
}	t_img;

typedef struct s_cub3d
{
	void	*mlx;
	void	*win;

	char	**map;
	char	**map_cp;

	t_img	*imgs;
	t_img	**textures;

	int		sky[3];
	int		floor[3];

	double	p_pos[2];
	double	p_dir[2];
	double	p_fov[2];
	double	p_old_dir;
	double	p_old_fov;
	double	p_rota;

	double	camera_x;
	double	ray_dir[2];
	int		ray_map[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	perpwalldist;

	int		step[2];
	int		hit;
	int		side;
	double	lineheight;

	int		draw_end;
	int		draw_start;
	int		x;
	double	wall_x;

	int		m;

	int		key_states[65536];
}	t_cub3d;

/***************************************************/
//-------------------CUB3D-------------------//
void	cub3d(char *file);

//-------------------DATA-------------------//
char	*make_file(char *str1, char *str2, char *str3, char *str4);
void	*make_data(t_cub3d *game, char *file, int *x, int *y);
void	make_data_map(t_cub3d *game);

//-------------------UTILS-------------------//
void	put_error(char *msg);
int		open_fd(char *file);
size_t	get_nb_inst(char **map, char c);
int		ft_close(int val_exit);
size_t	get_nb_line(char *file);
char	**get_map(char *file);
t_pos	get_coord(char **map, char c);
t_pos	get_suiv(char **map, t_pos ind, char c);
int		get_colour(int *tab, char *line);
void	get_file(t_cub3d *game, char *file);
void	str_exist(char *line, t_img **textures, int count_f, int count_c);

//---------GNL---------//
char	*get_str(int fd, char *str);
char	*ft_newstr(char *str, char *to_join);
char	*gnl_algo(char *str, char *leftrd);
char	*get_next_line(int fd);

//-------------------INIT-------------------//
void	init_game(char *file, t_cub3d *game);
void	init_angleplayer(t_cub3d *cub, char p);
void	init_player(t_cub3d *cub);
void	init_tex(t_cub3d *cub);
void	init_ray(t_cub3d *cub);

//-------------------PARSING-------------------//
void	flood_fill(char **map, size_t pos_x, size_t pos_y);
int		check_open(char **map);
int		check_path(char **map);
int		check_map(char **map);

//-------------------LIBFT-------------------//
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
size_t	ft_strlen(char const *str);
char	*ft_strdup(char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, char const *src, size_t n);
char	*ft_strjoin(char const *str, char const *s);
size_t	ft_strlcat(char *dest, char const *src, size_t n);

//-------------------RAYCASTING-------------------//
void	raycasting(t_cub3d *cub);
void	build_draw(t_cub3d *cub);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
int		choose_color(t_img *img, int x, int y);
t_img	*get_wall(t_cub3d *cub);

//-------------------MOVE-------------------//
void	move_player(t_cub3d *cub);

//---------mlx------
int		key_press(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);
void	*ft_calloc(size_t nmemb, size_t size);

//---------str------
char	*ft_strchr(const char *s, int c);

void	free_all(t_cub3d *cub);

#endif
