#include "get_next_line_bonus.h"
#include "cub3D.h"

size_t	get_nb_line(char *file)
{
	int		fd;
	size_t	nb_line;
	char	*line;

	fd = open_fd(file);
	if (fd < 0)
		return (-1);
	nb_line = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(EAST, line, ft_strlen(EAST))
			&& ft_strncmp(WEST, line, ft_strlen(WEST))
			&& ft_strncmp(NORTH, line, ft_strlen(NORTH))
			&& ft_strncmp(SOUTH, line, ft_strlen(SOUTH))
			&& line[0] != FLOOR && line[0] != CEILING
			&& ft_strlen(line) > 1)
			nb_line ++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb_line);
}

char	**get_map(char *file)
{
	char	**map;
	char	*line;
	size_t	ind;
	int		fd;
	int		is_valid;

	fd = open_fd(file);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (get_nb_line(file) + 1));
	if (!map)
		return (NULL);
	ind = 0;
	is_valid = 1;
	while (ind < get_nb_line(file))
	{
		line = get_next_line(fd);
		if (ft_strncmp(EAST, line, ft_strlen(EAST))
			&& ft_strncmp(WEST, line, ft_strlen(WEST))
			&& ft_strncmp(NORTH, line, ft_strlen(NORTH))
			&& ft_strncmp(SOUTH, line, ft_strlen(SOUTH))
			&& ft_strlen(line) > 1 && line[0] != FLOOR && line[0] != CEILING)
		{
			map[ind] = ft_substr(line, 0, ft_strlen(line) - 1);
			ind ++;
		}
		if (ft_strlen(line) <= 1)
		{
			is_valid = 0;
			if (ind > 0)
				is_valid = 2;
		}
		free(line);
	}
	map[ind] = NULL;
	close(fd);
	if (is_valid)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("An invalid character is in the file\n", 2);
		if (is_valid == 1)
			ft_putstr_fd("No line is spliting map from informations.\n", 2);
		else
			ft_putstr_fd("map is splited.\n", 2);
		ft_close(1);
	}
	return (map);
}

t_pos	get_coord(char **map, char c)
{
	t_pos	ind;

	ind.y = 0;
	while (map[ind.y])
	{
		ind.x = 0;
		while (map[ind.y][ind.x])
		{
			if (map[ind.y][ind.x] == c)
				return (ind);
			ind.x ++;
		}
		ind.y ++;
	}
	return (ind);
}

t_pos	get_suiv(char **map, t_pos ind, char c)
{
	while (map[ind.y])
	{
		while (map[ind.y][ind.x])
		{
			if (map[ind.y][ind.x] == c)
				return (ind);
			ind.x ++;
		}
		ind.x = 0;
		ind.y ++;
	}
	if (!map[ind.y])
		ind.y --;
	return (ind);
}

int	get_colour(int *tab, char *line)
{
	int	i;
	int	color;
	int	mult;
	int	count;

	color = -1;
	i = 1;
	while (++color < 3)
	{
		mult = 1;
		count = 0;
		tab[color] = 0;
		while (line[i] < '!' || line[i] > '~') // is_alnum
			i ++;
		if ('0' > line[i] || line[i] > '9') // modifier is_digit
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("line is corrupted\n", 1);
			ft_close(1);
		}
		while ('0' - 1 < line[i] && line[i] < '9' + 1) // is_digit
		{
			mult *= 10;
			i ++;
		}
		if (mult  > 1)
			i --;
		if (mult  > 10)
			i --;
		if (mult  > 100)
			i --;
		while ('0' - 1 < line[i] && line[i] < '9' + 1) // is_digit
		{
			mult /= 10;
			tab[color] += mult * (line[i] - '0');
			count ++;
			if (count > 3 || tab[color] > 255)
			{
				ft_putstr_fd(ERROR, 2);
				ft_putstr_fd("max value for color is 255\n", 1);
				ft_close(1);
			}
			i++;
		}
		i ++;
	}
	while (line[i])
	{
		if (' ' - 1 < line[i] && line[i] < 127) // is_alnum
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("line is corrupted\n", 1);
			ft_close(1);
		}
		i++;
	}
	return (1);
}


void	get_file(t_game *game, char *file)
{
	int		fd;
	int		i;
	int		count;
	size_t	nb_line;
	char	*line;

	fd = open_fd(file);
	if (fd < 0)
		return;
	line = get_next_line(fd);
	count = 0;
	i = 0;
	while (line)
	{

		if ((!ft_strncmp(EAST, line, ft_strlen(EAST)) && game->wall_files[0])
			|| (!ft_strncmp(WEST, line, ft_strlen(WEST)) && game->wall_files[2])
			|| (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && game->wall_files[1])
			|| (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && game->wall_files[3])
			|| count > 2)
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("line duplicates\n", 1);
			ft_close(1);
		}
		if (!ft_strncmp(EAST, line, ft_strlen(EAST)) && !game->wall_files[0])
			game->wall_files[0] = ft_strdup(line + 1 + ft_strlen(WEST));
		if (!ft_strncmp(WEST, line, ft_strlen(WEST)) && !game->wall_files[2])
			game->wall_files[2] = ft_strdup(line + 1 + ft_strlen(WEST));
		if (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && !game->wall_files[1])
			game->wall_files[1] = ft_strdup(line + 1 + ft_strlen(NORTH));
		if (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && !game->wall_files[3])
			game->wall_files[3] = ft_strdup(line + 1 + ft_strlen(SOUTH));
		if (line[0] == FLOOR)
			count += get_colour(game->floor, line);
		if (line[0] == CEILING)
			count += get_colour(game->ceil, line);
		free(line);
		line = get_next_line(fd);
	}
	if (count < 2)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("missing color information(s)\n", 1);
		ft_close(1);
	}

	i = -1;
	while (++i < NB_DIR)
	{
		if (!game->wall_files[i] || ft_strlen(game->wall_files[i]) <= ft_strlen(XPM))
		{
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd("missing texture(s) .xpm file\n", 1);
			ft_close(1);
		}
	}
	close(fd);
}
