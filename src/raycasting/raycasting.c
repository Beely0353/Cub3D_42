/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:57:46 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/13 19:36:21 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_init(t_cub3d *cub)
{
	cub->cameraX = 2 * cub->x / (double) WIDTH - 1;
	cub->rayMap[0] = (int)cub->p_pos[0];
	cub->rayMap[1] = (int)cub->p_pos[1];
	cub->rayDir[0] = cub->p_dir[0] + cub->p_FOV[0] * cub->cameraX;
	cub->rayDir[1] = cub->p_dir[1] + cub->p_FOV[1] * cub->cameraX;
	if (cub->rayDir[0] == 0)
		cub->deltaDist[0] = INFINITY;
	else
		cub->deltaDist[0] = fabs(1 / cub->rayDir[0]);
	if (cub->rayDir[1] == 0)
		cub->deltaDist[1] = INFINITY;
	else
		cub->deltaDist[1] = fabs(1 / cub->rayDir[1]);
	cub->hit = 0;
}

void	ray_calcdist(t_cub3d *cub)
{
	if (cub->rayDir[0] < 0)
	{
		cub->step[0] = -1;
		cub->sideDist[0] = (cub->p_pos[0] - cub->rayMap[0]) * cub->deltaDist[0];
	}
	else
	{
		cub->step[0] = 1;
		cub->sideDist[0] = (cub->rayMap[0] + 1.0 - cub->p_pos[0]) \
		* cub->deltaDist[0];
	}
	if (cub->rayDir[1] < 0)
	{
		cub->step[1] = -1;
		cub->sideDist[1] = (cub->p_pos[1] - cub->rayMap[1]) * cub->deltaDist[1];
	}
	else
	{
		cub->step[1] = 1;
		cub->sideDist[1] = (cub->rayMap[1] + 1.0 - \
		cub->p_pos[1]) * cub->deltaDist[1];
	}
}

void	ray_dda(t_cub3d *cub)
{
	while (cub->hit == 0)
	{
		if (cub->sideDist[0] < cub->sideDist[1])
		{
			cub->sideDist[0] += cub->deltaDist[0];
			cub->rayMap[0] += cub->step[0];
			cub->side = 0;
		}
		else
		{
			cub->sideDist[1] += cub->deltaDist[1];
			cub->rayMap[1] += cub->step[1];
			cub->side = 1;
		}
		if (cub->map[cub->rayMap[0]][cub->rayMap[1]] == '1')
			cub->hit = 1;
		//printf("%d\n", cub->hit);
	}
}

void	ray_calcdraw(t_cub3d *cub)
{
	if (cub->side == 0)
		cub->perpWallDist = (cub->sideDist[0] - cub->deltaDist[0]);
	else
		cub->perpWallDist = (cub->sideDist[1] - cub->deltaDist[1]);
	if (cub->side)
		cub->wallX = cub->p_pos[0] + cub->perpWallDist * cub->rayDir[0];
	else
		cub->wallX = cub->p_pos[1] + cub->perpWallDist * cub->rayDir[1];
	//printf("sideDist[0] %f deltaDist[0] %f\n", cub->sideDist[0], cub->deltaDist[0]);
	//printf("sideDist[1] %f deltaDist[1] %f\n", cub->sideDist[1], cub->deltaDist[1]);
	cub->wallX -= floor(cub->wallX);
	//printf("start %f\n", cub->wallX);
	cub->lineHeight = HEIGHT / cub->perpWallDist;
	cub->drawStart = (int)(-cub->lineHeight / 2) + (HEIGHT / 2);
	cub->drawEnd = (int)cub->lineHeight / 2 + HEIGHT / 2;
	//printf("start %f\n", cub->lineHeight);
	//printf("start %d end %d\n", cub->drawStart, cub->drawEnd);
}

void	raycasting(t_cub3d *cub)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cub->x = x;
		ray_init(cub);
		ray_calcdist(cub);
		ray_dda(cub);
		ray_calcdraw(cub);
		build_draw(cub);
		x++;
	}
	//printf("dirx %f diry %f\n", cub->p_dir[0], cub->p_dir[1]);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->img, 0, 0);
}