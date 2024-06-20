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

void put_error(char *msg)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(msg, 2);
	ft_close(1);
}

int	open_fd(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		put_error("Directory is open\n");
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			put_error("File didn't open correctly\n");
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
