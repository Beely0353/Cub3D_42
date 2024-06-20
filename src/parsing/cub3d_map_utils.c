/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:35:55 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/20 18:31:45 by biaroun          ###   ########.fr       */
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
		(*ind)++;
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
