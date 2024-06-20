/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:35:55 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:35:56 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_nb_line(char *file)
{
	int		fd;
	size_t	nb_line;
	char	*line;

	fd = open_fd(file);
	if (fd < 0)
		return (-1);
	nb_line = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(EAST, line, ft_strlen(EAST))
			&& ft_strncmp(WEST, line, ft_strlen(WEST))
			&& ft_strncmp(NORTH, line, ft_strlen(NORTH))
			&& ft_strncmp(SOUTH, line, ft_strlen(SOUTH))
			&& line[0] != FLOOR && line[0] != CEILING
			&& ft_strlen(line) > 1)
			nb_line ++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb_line);
}

int	check_line(char **dest, char *line, size_t *ind, int is_valid)
{
	if (ft_strncmp(EAST, line, ft_strlen(EAST))
		&& ft_strncmp(WEST, line, ft_strlen(WEST))
		&& ft_strncmp(NORTH, line, ft_strlen(NORTH))
		&& ft_strncmp(SOUTH, line, ft_strlen(SOUTH))
		&& line[0] != FLOOR && line[0] != CEILING
		&& ft_strlen(line) > 1)
	{
		dest[*ind] = ft_substr(line, 0, ft_strlen(line) - 1);
		(*ind) ++;
	}
	if (ft_strlen(line) <= 1)
	{
		if (*ind > 0)
			is_valid = 2;
		is_valid = 0;
	}
	return (is_valid);
}

void	map_is_valid(int is_valid)
{
	if (is_valid)
		ft_putstr_fd("An invalid character is in the file\n", 2);
	if (is_valid == 1)
		put_error("No line is spliting map from informations.\n");
	else if (is_valid == 2)
		put_error("map is splited.\n");
}

char	**get_map(char *file)
{
	char	**map;
	char	*line;
	size_t	ind;
	int		fd;
	int		is_valid;

	fd = open_fd(file);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (get_nb_line(file) + 1));
	if (!map)
		return (NULL);
	ind = 0;
	is_valid = 1;
	while (ind < get_nb_line(file))
	{
		line = get_next_line(fd);
		is_valid = check_line(map, line, &ind, is_valid);
		free(line);
	}
	map[ind] = NULL;
	close(fd);
	map_is_valid(is_valid);
	return (map);
}

t_pos	get_coord(char **map, char c)
{
	t_pos	ind;

	ind.y = 0;
	while (map[ind.y])
	{
		ind.x = 0;
		while (map[ind.y][ind.x])
		{
			if (map[ind.y][ind.x] == c)
				return (ind);
			ind.x ++;
		}
		ind.y ++;
	}
	return (ind);
}

t_pos	get_suiv(char **map, t_pos ind, char c)
{
	while (map[ind.y])
	{
		while (map[ind.y][ind.x])
		{
			if (map[ind.y][ind.x] == c)
				return (ind);
			ind.x ++;
		}
		ind.x = 0;
		ind.y ++;
	}
	if (!map[ind.y])
		ind.y --;
	return (ind);
}

int	color_calcul(char *line, size_t *i)
{
	int	mult;
	int	color_val;

	mult = 1;
	(*i) --;
	while (++(*i) && '0' - 1 < line[*i] && line[*i] < '9' + 1)
		mult *= 10;
	while ('0' - 1 < line[*i - 1] && line[*i - 1] < '9' + 1)
		(*i) --;
	color_val = 0;
	while ('0' - 1 < line[*i] && line[*i] < '9' + 1)
	{
		mult /= 10;
		color_val += mult * (line[*i] - '0');
		if (color_val > 255)
			put_error("max value for color is 255\n");
		(*i) ++;
	}
	return (color_val);
}

int	get_colour(int *tab, char *line)
{
	size_t	i;
	int		color;

	color = -1;
	i = 1;
	while (++color < 3)
	{
		if (i >= ft_strlen(line)
			|| (i < 2 && (line[i] > ' ' && line[i] < '~')))
			put_error("line is corrupted\n");
		while (line[i] < '!' || line[i] > '~')
			i ++;
		if ((line[i] > ' ' && line[i] < '0') || line[i] > '9')
			put_error("line is corrupted\n");
		tab[color] = color_calcul(line, &i);
		while (line[i] < '!' || line[i] > '~')
			i ++;
		i ++;
	}
	i -= 2;
	while (line[++i])
		if (i < ft_strlen(line) + 1
			&& ' ' < line[i] && line[i] < '~' + 1)
			put_error("line is corrupted\n");
	return (1);
}

void	str_exist(char *line, t_img **texts, int count_f, int count_c)
{
	int	count;

	count = count_f + count_c;
	if ((!ft_strncmp(EAST, line, ft_strlen(EAST)) && texts[0]->file)
		|| (!ft_strncmp(WEST, line, ft_strlen(WEST)) && texts[2]->file)
		|| (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && texts[1]->file)
		|| (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && texts[3]->file)
		|| count > 2)
		put_error("line duplicates\n");
	if (!ft_strncmp(EAST, line, ft_strlen(EAST)) && !texts[0]->file)
		texts[0]->file = ft_strdup(line + 1 + ft_strlen(WEST));
	if (!ft_strncmp(WEST, line, ft_strlen(WEST)) && !texts[2]->file)
		texts[2]->file = ft_strdup(line + 1 + ft_strlen(WEST));
	if (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && !texts[1]->file)
		texts[1]->file = ft_strdup(line + 1 + ft_strlen(NORTH));
	if (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && !texts[3]->file)
		texts[3]->file = ft_strdup(line + 1 + ft_strlen(SOUTH));
}

void	get_file(t_cub3d *game, char *file)
{
	int		fd;
	int		i;
	int		count_f;
	int		count_c;
	char	*line;

	fd = open_fd(file);
	if (fd < 0)
		return;
	count_f = 0;
	count_c = 0;
	line = get_next_line(fd);
	while (line)
	{
		str_exist(line, game->textures, count_f, count_c);
		if (line[0] == FLOOR)
			count_f += get_colour(game->floor, line);
		if (line[0] == CEILING)
			count_c += get_colour(game->sky, line);
		free(line);
		line = get_next_line(fd);
	}
	i = -1;
	while (++i < NB_DIR)
	{
		if (count_c < 1 || count_f < 1 || !game->textures[i]->file
			|| ft_strlen(game->textures[i]->file) <= ft_strlen(XPM))
			put_error("missing .xpm file(s) or color information(s)\n");
	}
	close(fd);
}
