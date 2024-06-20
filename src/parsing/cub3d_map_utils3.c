/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:41:21 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/20 18:41:37 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
