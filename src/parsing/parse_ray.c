/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:16:43 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:08:38 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_angleplayer2(t_cub3d *cub, char p)
{
	if (p == 'E')
	{
		cub->p_rota = -(PI / 4);
		cub->p_dir[0] = 0;
		cub->p_dir[1] = 1;
		cub->p_fov[0] = -0.66;
		cub->p_fov[1] = 0;
	}
	else if (p == 'W')
	{
		cub->p_rota = (PI / 4);
		cub->p_dir[0] = 0;
		cub->p_dir[1] = -1;
		cub->p_fov[0] = 0.66;
		cub->p_fov[1] = 0;
	}
}

void	init_angleplayer(t_cub3d *cub, char p)
{
	if (p == 'N')
	{
		cub->p_rota = (PI / 4);
		cub->p_dir[0] = -1;
		cub->p_dir[1] = 0;
		cub->p_fov[0] = 0;
		cub->p_fov[1] = 0.66;
	}
	else if (p == 'S')
	{
		cub->p_rota = (PI / 4);
		cub->p_dir[0] = 1;
		cub->p_dir[1] = 0;
		cub->p_fov[0] = 0;
		cub->p_fov[1] = -0.66;
	}
	else if (p == 'E' || p == 'W')
		init_angleplayer2(cub, p);
}

void	init_player(t_cub3d *cub)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = cub->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				cub->p_pos[0] = (double)i + 0.5;
				cub->p_pos[1] = (double)j + 0.5;
				init_angleplayer(cub, map[i][j]);
			}
			j++;
		}
		i++;
	}
}

void	init_tex(t_cub3d *cub)
{
	int	i;

	cub->imgs = calloc(1, sizeof(t_img));
	if (!cub->imgs)
		put_error("allocating images\n");
	cub->imgs->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->imgs->addr = mlx_get_data_addr(cub->imgs->img,
			&cub->imgs->bits_per_pixel,
			&cub->imgs->line_length, &cub->imgs->endian);
	i = -1;
	while (++i < NB_DIR)
		cub->textures[i]->addr = mlx_get_data_addr(cub->textures[i]->img,
				&cub->textures[i]->bits_per_pixel,
				&cub->textures[i]->line_length,
				&cub->textures[i]->endian);
}

void	init_ray(t_cub3d *cub)
{
	cub->camera_x = 0;
	cub->ray_dir[0] = 0;
	cub->ray_dir[1] = 0;
	cub->ray_map[0] = 0;
	cub->ray_map[1] = 0;
	cub->side_dist[0] = 0;
	cub->side_dist[1] = 0;
	cub->delta_dist[0] = 0;
	cub->delta_dist[1] = 0;
	cub->perpwalldist = 0;
	cub->step[0] = 0;
	cub->step[1] = 0;
	cub->hit = 0;
	cub->side = 0;
	cub->lineheight = 0;
	cub->draw_end = 0;
	cub->draw_start = 0;
	cub->x = -1;
	cub->wall_x = 0;
	cub->m = 0;
	while (++cub->x < 65536)
		cub->key_states[cub->x] = 0;
	cub->x = 0;
}
