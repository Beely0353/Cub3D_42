/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:57:46 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:19:49 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_init(t_cub3d *cub)
{
	cub->camera_x = 2 * cub->x / (double) WIDTH - 1;
	cub->ray_map[0] = (int)cub->p_pos[0];
	cub->ray_map[1] = (int)cub->p_pos[1];
	cub->ray_dir[0] = cub->p_dir[0] + cub->p_fov[0] * cub->camera_x;
	cub->ray_dir[1] = cub->p_dir[1] + cub->p_fov[1] * cub->camera_x;
	if (cub->ray_dir[0] == 0)
		cub->delta_dist[0] = INFINITY;
	else
		cub->delta_dist[0] = fabs(1 / cub->ray_dir[0]);
	if (cub->ray_dir[1] == 0)
		cub->delta_dist[1] = INFINITY;
	else
		cub->delta_dist[1] = fabs(1 / cub->ray_dir[1]);
	cub->hit = 0;
}

void	ray_calcdist(t_cub3d *cub)
{
	if (cub->ray_dir[0] < 0)
	{
		cub->step[0] = -1;
		cub->side_dist[0] = (cub->p_pos[0] - cub->ray_map[0])
			* cub->delta_dist[0];
	}
	else
	{
		cub->step[0] = 1;
		cub->side_dist[0] = (cub->ray_map[0] + 1.0 - cub->p_pos[0]) \
		* cub->delta_dist[0];
	}
	if (cub->ray_dir[1] < 0)
	{
		cub->step[1] = -1;
		cub->side_dist[1] = (cub->p_pos[1] - cub->ray_map[1])
			* cub->delta_dist[1];
	}
	else
	{
		cub->step[1] = 1;
		cub->side_dist[1] = (cub->ray_map[1] + 1.0 - \
		cub->p_pos[1]) * cub->delta_dist[1];
	}
}

void	ray_dda(t_cub3d *cub)
{
	while (cub->hit == 0)
	{
		if (cub->side_dist[0] < cub->side_dist[1])
		{
			cub->side_dist[0] += cub->delta_dist[0];
			cub->ray_map[0] += cub->step[0];
			cub->side = 0;
		}
		else
		{
			cub->side_dist[1] += cub->delta_dist[1];
			cub->ray_map[1] += cub->step[1];
			cub->side = 1;
		}
		if (cub->map[cub->ray_map[0]][cub->ray_map[1]] == '1')
			cub->hit = 1;
	}
}

void	ray_calcdraw(t_cub3d *cub)
{
	if (cub->side == 0)
		cub->perpwalldist = (cub->side_dist[0] - cub->delta_dist[0]);
	else
		cub->perpwalldist = (cub->side_dist[1] - cub->delta_dist[1]);
	if (cub->side)
		cub->wall_x = cub->p_pos[0] + cub->perpwalldist * cub->ray_dir[0];
	else
		cub->wall_x = cub->p_pos[1] + cub->perpwalldist * cub->ray_dir[1];
	cub->wall_x -= floor(cub->wall_x);
	cub->lineheight = HEIGHT / cub->perpwalldist;
	cub->draw_start = (int)(-cub->lineheight / 2) + (HEIGHT / 2);
	cub->draw_end = (int)cub->lineheight / 2 + HEIGHT / 2;
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
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->img, 0, 0);
}
