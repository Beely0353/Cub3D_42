#include "cub3D.h"

t_game	cub3D(char *file)
{
	t_game	game;

	game.vars.map_cp = get_map(file);
	if (!game.vars.map_cp || check_map(game.vars.map_cp))
		ft_close(1);
	init_game(&game, file);
	if (!game.vars.map)
		ft_close(1);
	ft_close(0);
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	game;
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
	fd = open_fd(argv[1]);
	if (fd >= 0)
		game = cub3D(argv[1]);
	return (0);
}
