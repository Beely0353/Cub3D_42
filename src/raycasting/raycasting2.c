/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:07:33 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/11 22:02:24 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_floor(t_cub3d *cub)
{
	int	x;
	int	y;

	x = cub->x;
	y = cub->drawEnd;
	if (y < 0 || y > HEIGHT)
		y = HEIGHT;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(&cub->imgs, x, y, \
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
	/ (double)(cub->drawEnd - cub->drawStart));
	if (cub->drawStart < 0)
	{
		y_texture = step * cub->drawStart * -1;
		cub->drawStart = 0;
	}
	y = cub->drawStart;
	while (y < cub->drawEnd)
	{
		if (y >= HEIGHT)
			break ;
		my_mlx_pixel_put(&cub->imgs, cub->x, y, \
		choose_color(texture, cub->wallX * (double)texture->width, y_texture));
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
	while (y < cub->drawStart)
	{
		my_mlx_pixel_put(&cub->imgs, x, y, \
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
