/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:16:43 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/11 23:17:07 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_angleplayer(t_cub3d *cub, char p)
{
	if (p == 'N')
	{
		cub->p_rota = (PI / 4);
		cub->p_dir[0] = -1;
		cub->p_dir[1] = 0;
	}
	else if (p == 'S')
	{
		cub->p_rota = -(PI / 4);
		cub->p_dir[0] = 1;
		cub->p_dir[1] = 0;
	}
	else if (p == 'E')
	{
		cub->p_rota = (PI / 4);
		cub->p_dir[0] = 0;
		cub->p_dir[1] = 1;
	}
	else if (p == 'W')
	{
		cub->p_rota = -(PI / 4);
		cub->p_dir[0] = 0;
		cub->p_dir[1] = -1;
	}
}


void init_player(t_cub3d *cub)
{
	int 	i;
	int 	j;
	char 	**map;

	i = 0;
	j = 0;
	map = cub->map_cp;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'O')
			{
				cub->p_pos[0] = j;
				cub->p_pos[1] = i;
				init_angleplayer(cub, map[i][j]);
			}
			j++;
		}
		i++;
	}
}

void init_tex(t_cub3d *cub)
{
	cub->imgs->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->imgs->addr = mlx_get_data_addr(cub->imgs->img, &cub->imgs->bits_per_pixel, &cub->imgs->line_length, &cub->imgs->endian);
	cub->textures[0]->addr = mlx_get_data_addr(cub->textures[0]->img, &cub->textures[0].bits_per_pixel, &cub->textures[0]->line_length, &cub->textures[0]->endian);
	cub->textures[1]->addr = mlx_get_data_addr(cub->textures[1]->img, &cub->textures[1]->bits_per_pixel, &cub->textures[1]->line_length, &cub->textures[1]->endian);
	cub->textures[2]->addr = mlx_get_data_addr(cub->textures[2]->img, &cub->textures[2]->bits_per_pixel, &cub->textures[2]->line_length, &cub->textures[2]->endian);
	cub->textures[3]->addr = mlx_get_data_addr(cub->textures[3]->img, &cub->textures[3]->bits_per_pixel, &cub->textures[3]->line_length, &cub->textures[3]->endian);
}

void init_ray(t_cub3d *cub)
{
	cub->cameraX = 0;
	cub->rayDir[0] = 0;
	cub->rayDir[1] = 0;
	cub->rayMap[0] = 0;
	cub->rayMap[1] = 0;
	cub->sideDist[0] = 0;
	cub->sideDist[1] = 0;
	cub->deltaDist[0] = 0;
	cub->deltaDist[1] = 0;
	cub->perpWallDist = 0;
	cub->step[0] = 0;
	cub->step[1] = 0;
	cub->hit = 0;
	cub->side = 0;
	cub->lineHeight = 0;
	cub->drawEnd = 0;
	cub->drawStart = 0;
	cub->x = 0;
	cub->wallX = 0;
	cub->m = 0;
}