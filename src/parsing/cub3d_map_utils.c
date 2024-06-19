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
		&& ft_strlen(line) > 1 && line[0] != FLOOR && line[0] != CEILING)
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
	if (is_valid)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("An invalid character is in the file\n", 2);
		if (is_valid == 1)
			ft_putstr_fd("No line is spliting map from informations.\n", 2);
		else
			ft_putstr_fd("map is splited.\n", 2);
		ft_close(1);
	}
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
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("max value for color is 255\n", 1);
			ft_close(1);
		}
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
		if (i >= ft_strlen(line) || (i < 2 && (line[i] > '!' && line[i] < '~')))
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("line is corrupted\n", 1);
			ft_close(1);
		}
		while (line[i] < '!' || line[i] > '~')
			i ++;
		if ('0' > line[i] || line[i] > '9')
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("line is corrupted\n", 1);
			ft_close(1);
		}
		tab[color] = color_calcul(line, &i);
		i ++;
	}
	i --;
	while (line[i])
	{
		if (' ' < line[i] && line[i] < '~' + 1)
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("line is corrupted\n", 1);
			ft_close(1);
		}
		i ++;
	}
	return (1);
}

void	str_exist(char *line, t_img **textures, int count_f, int count_c)
{
	int	count;

	count = count_f + count_c;
	if ((!ft_strncmp(EAST, line, ft_strlen(EAST)) && textures[0]->file)
		|| (!ft_strncmp(WEST, line, ft_strlen(WEST)) && textures[2]->file)
		|| (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && textures[1]->file)
		|| (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && textures[3]->file)
		|| count > 2)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("line duplicates\n", 1);
		ft_close(1);
	}
	if (!ft_strncmp(EAST, line, ft_strlen(EAST)) && !textures[0]->file)
		textures[0]->file = ft_strdup(line + 1 + ft_strlen(WEST));
	if (!ft_strncmp(WEST, line, ft_strlen(WEST)) && !textures[2]->file)
		textures[2]->file = ft_strdup(line + 1 + ft_strlen(WEST));
	if (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && !textures[1]->file)
		textures[1]->file = ft_strdup(line + 1 + ft_strlen(NORTH));
	if (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && !textures[3]->file)
		textures[3]->file = ft_strdup(line + 1 + ft_strlen(SOUTH));
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
		if (count_c < 1 || count_f < 1 || !game->textures[i]->file || ft_strlen(game->textures[i]->file) <= ft_strlen(XPM))
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("missing texture(s) .xpm file(s) or\n", 1);
			ft_putstr_fd("missing color information(s)\n", 1);
			ft_close(1);
		}
	}
	close(fd);
}
