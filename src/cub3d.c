/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:52:04 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 18:53:41 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(char *file)
{
	t_cub3d	*game;

	game = malloc(sizeof(t_cub3d));
	if (!game)
	{
		perror("while allocating\n");
		exit(-1);
	}
	game->map_cp = get_map(file);
	if (!game->map_cp || check_map(game->map_cp))
		ft_close(1);
	init_game(file, game);
	if (!game->map)
		ft_close(1);
	raycasting(game);
	mlx_hook(game->win, 2, 1L << 0, (void *)key_press, game);
	mlx_hook(game->win, 3, 1L << 1, (void *)key_release, game);
	mlx_loop_hook(game->mlx, (void *)move_player, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	size_t	len;

	if (argc != 2)
	{
		perror("required argument number is 2\n");
		return (-1);
	}
	len = ft_strlen(CUB);
	if (argv[1][ft_strlen(argv[1]) - len - 1] == '/'
		|| ft_strncmp(&argv[1][ft_strlen(argv[1]) - len], CUB, len))
	{
		perror("File not compatible\n");
		return (-1);
	}
	fd = open_fd(argv[1]);
	if (fd >= 0)
		cub3d(argv[1]);
	return (0);
}
