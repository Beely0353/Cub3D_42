/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:52:04 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/11 23:24:04 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(char *file, t_cub3d *game)
{
	game->map_cp = get_map(file);
	if (!game->map_cp || check_map(game->map_cp))
		ft_close(1);
	init_game(file, game);
	if (!game->map)
		ft_close(1);

	mlx_hook(game->win, 2, 1L<<0, (void *)key_press, game);
	mlx_hook(game->win, 3, 1L<<1, (void *)key_release, game);
	mlx_loop_hook(game->mlx, (void *)move_player, game);


//	mlx_hook(game->win, 17, 0, (void *)free_all, game);


	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_cub3d	*game;
	int		fd;
	size_t	len;
	if (argc != 2)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("required argument number is 2\n", 2);
		return (-1);
	}
	len = ft_strlen(CUB);
	if (argv[1][ft_strlen(argv[1]) - len - 1] == '/'
		|| ft_strncmp(&argv[1][ft_strlen(argv[1]) - len], CUB, len))
	{
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("File not compatible\n", 2);
		return (-1);
	}
	game = malloc(sizeof(t_cub3d));
	if (!game)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("while allocating\n", 2);
		return (-1);
	}
	fd = open_fd(argv[1]);

	if (fd >= 0)
		cub3d(argv[1], game);
	return (0);
}
