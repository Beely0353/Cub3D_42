/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:07:33 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:08:29 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_floor(t_cub3d *cub)
{
	int	x;
	int	y;

	x = cub->x;
	y = cub->draw_end;
	while (y < HEIGHT - 1)
	{
		my_mlx_pixel_put(cub->imgs, x, y, \
		create_trgb(0, cub->floor[0], cub->floor[1], cub->floor[2]));
		y++;
	}
}

void	set_wall(t_cub3d *cub)
{
	int		y;
	double	y_texture;
	double	step;
	t_img	*texture;

	texture = get_wall(cub);
	y_texture = 0;
	step = (double)((double)texture->height \
	/ (double)(cub->draw_end - cub->draw_start));
	if (cub->draw_start < 0)
	{
		y_texture = step * cub->draw_start * -1;
		cub->draw_start = 0;
	}
	y = cub->draw_start;
	while (y < cub->draw_end)
	{
		if (y >= HEIGHT)
			break ;
		my_mlx_pixel_put(cub->imgs, cub->x, y, \
		choose_color(texture, cub->wall_x * (double)texture->width, y_texture));
		y++;
		y_texture += step;
	}
}

void	set_sky(t_cub3d *cub)
{
	int	x;
	int	y;

	x = cub->x;
	y = 0;
	while (y < cub->draw_start)
	{
		my_mlx_pixel_put(cub->imgs, x, y, \
		create_trgb(0, cub->sky[0], cub->sky[1], cub->sky[2]));
		y++;
	}
}

void	build_draw(t_cub3d *cub)
{
	set_floor(cub);
	set_wall(cub);
	set_sky(cub);
}
