/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:27:32 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/10 17:27:33 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_game(t_game *game, char *file)
{
	int	i;

	game->vars.mlx = mlx_init();
	if (!game->vars.mlx)
		return ;
	game->vars.win = mlx_new_window(game->vars.mlx, WIN_L, WIN_H, NAME);
	if (!game->vars.win)
	{
		free(game->vars.mlx);
		return ;
	}
	game->vars.map = get_map(file);
	if (!game->vars.map)
	{
		free(game->vars.mlx);
		free(game->vars.win);
		return ;
	}
	i = -1;
	while (++i < NB_DIR)
		game->wall_files[i] = NULL;
	get_file(game, file);
	i = -1;
	while (++i < NB_DIR)
		game->wall_files[i][ft_strlen(game->wall_files[i]) - 1] = '\0';
	make_data_map(game);
	ft_putstr_fd("ok\n", 0);
	ft_close(0);
}
