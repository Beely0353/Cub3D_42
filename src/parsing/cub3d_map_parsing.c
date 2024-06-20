/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:27:36 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/20 18:41:59 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_open(char **map)
{
	t_pos	ind;
	size_t	nb_line;

	nb_line = 0;
	while (map[nb_line])
		nb_line ++;
	ind.y = 0;
	while (map[ind.y])
	{
		ind.x = 0;
		while (map[ind.y][ind.x])
		{
			if (map[ind.y][ind.x] == PS || map[ind.y][ind.x] == PW
				|| map[ind.y][ind.x] == PN
				|| map[ind.y][ind.x] == PE)
				flood_fill(map, ind.x, ind.y);
			ind.x ++;
		}
		ind.y ++;
	}
	return (0);
}

void	flood_fill(char **map, size_t pos_x, size_t pos_y)
{
	size_t	i;

	i = 0;
	while (map[i])
		i ++;
	if (map[pos_y][pos_x] != WALL && map[pos_y][pos_x] != GROUND
		&& map[pos_y][pos_x] != PS && map[pos_y][pos_x] != PW
		&& map[pos_y][pos_x] != PN && map[pos_y][pos_x] != PE
		&& map[pos_y][pos_x])
		put_error("An invalid character is in the file\n");
	if (!pos_x || pos_x == ft_strlen(map[pos_y]) || !pos_y || pos_y == i)
		put_error("Map is open (extemity can be reach)\n");
	if (map[pos_y][pos_x] == WALL)
		return ;
	map[pos_y][pos_x] = WALL;
	if (pos_x > 0 && map[pos_y][pos_x - 1] != WALL)
		flood_fill(map, pos_x - 1, pos_y);
	if (pos_x < ft_strlen(map[pos_y]) && map[pos_y][pos_x + 1] != WALL)
		flood_fill(map, pos_x + 1, pos_y);
	if (pos_y > 0 && map[pos_y - 1][pos_x] != WALL)
		flood_fill(map, pos_x, pos_y - 1);
	if (pos_y < i && map[pos_y + 1][pos_x] != WALL)
		flood_fill(map, pos_x, pos_y + 1);
}

int	check_path(char **map)
{
	t_pos	ind;

	ind.y = 0;
	while (map[ind.y])
	{
		ind.x = 0;
		while (map[ind.y][ind.x])
		{
			if (map[ind.y][ind.x] != WALL
				&& map[ind.y][ind.x] != GROUND
				&& map[ind.y][ind.x] != PS
				&& map[ind.y][ind.x] != PW
				&& map[ind.y][ind.x] != PN
				&& map[ind.y][ind.x] != PE
				&& map[ind.y][ind.x] != ' '
				&& map[ind.y][ind.x])
				return (-1);
			ind.x ++;
		}
		ind.y ++;
	}
	return (0);
}

int	check_map(char **map)
{
	int	inst;

	inst = get_nb_inst(map, PS) + get_nb_inst(map, PW)
		+ get_nb_inst(map, PN) + get_nb_inst(map, PE);
	if (!map || inst != 1)
		put_error("Invalid number of player, start instance\n");
	if (check_path(map))
		put_error("An invalid character is in the file\n");
	if (check_open(map))
		put_error("Map is open\n");
	return (0);
}
