/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_game_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:28:37 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:28:38 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_fd(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd(ERROR, 1);
		ft_putstr_fd("Directory is open\n", 1);
		close(fd);
		ft_close(1);
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(ERROR, 1);
			ft_putstr_fd("File didn't open correctly\n", 1);
		}
	}
	return (fd);
}

size_t	get_nb_inst(char **map, char c)
{
	size_t	ent;
	t_pos	ind;

	ent = 0;
	ind.y = 0;
	while (map[ind.y])
	{
		ind.x = 0;
		while (map[ind.y][ind.x])
		{
			if (map[ind.y][ind.x] == c)
				ent ++;
			ind.x ++;
		}
		ind.y ++;
	}
	return (ent);
}

int	ft_close(int val_exit)
{
	exit(val_exit);
	return (val_exit);
}
