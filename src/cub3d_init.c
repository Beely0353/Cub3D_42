#include "cub3d.h"

void	make_mlx_items(t_cub3d *game, char *file)
{
	int	i;

	i = -1;
	while (++i < NB_DIR)
		game->textures[i].addr = NULL;
	get_file(game, file);
	i = -1;
	while (++i < NB_DIR)
		game->textures[i].addr[ft_strlen(game->textures[i].addr) - 1] = '\0';
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
