/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:33:51 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:33:52 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_mlx_items(t_cub3d *game, char *file)
{
	int	i;

	game->textures = malloc(NB_DIR * sizeof(t_img *));
	if (!game->textures)
		put_error("allocating textures\n");
	i = -1;
	while (++i < NB_DIR)
	{
		game->textures[i] = malloc(sizeof(t_img));
		if (!game->textures)
			put_error("allocating textures\n");
		game->textures[i]->file = NULL;
		game->textures[i]->addr = NULL;
	}
	get_file(game, file);
	make_data_map(game);
}

void	init_game(char *file, t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return ;
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, NAME);
	if (!game->win)
	{
		free(game->mlx);
		return ;
	}
	game->map = get_map(file);
	if (!game->map)
	{
		free(game->mlx);
		free(game->win);
		return ;
	}
	init_player(game);
	init_ray(game);
	make_mlx_items(game, file);
}
