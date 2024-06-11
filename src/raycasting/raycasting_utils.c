/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:11:00 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/11 22:10:44 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	choose_color(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

t_img	*get_wall(t_cub3d *cub)//a changer
{
	if (cub->side && cub->step[1] < 0)
		return (cub->textures[1]);
	if (cub->side && cub->step[1] > 0)
		return (cub->textures[3]);
	if (!cub->side && cub->step[0] < 0)
		return (cub->textures[2]);
	if (!cub->side && cub->step[0] > 0)
		return (cub->textures[0]);
	return (cub->textures[1]);
}
