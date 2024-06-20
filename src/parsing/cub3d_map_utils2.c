/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:28:57 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/20 18:47:41 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_calcul(char *line, size_t *i)
{
	int	mult;
	int	color_val;

	mult = 1;
	(*i)--;
	while (++(*i) && '0' - 1 < line[*i] && line[*i] < '9' + 1)
		mult *= 10;
	while ('0' - 1 < line[*i - 1] && line[*i - 1] < '9' + 1)
		(*i)--;
	color_val = 0;
	while ('0' - 1 < line[*i] && line[*i] < '9' + 1)
	{
		mult /= 10;
		color_val += mult * (line[*i] - '0');
		if (color_val > 255)
			put_error("max value for color is 255\n");
		(*i)++;
	}
	return (color_val);
}

int	get_colour(int *tab, char *line)
{
	size_t	i;
	int		color;

	color = -1;
	i = 1;
	while (++color < 3)
	{
		if (i >= ft_strlen(line)
			|| (i < 2 && (line[i] > ' ' && line[i] < '~')))
			put_error("line is corrupted\n");
		while (line[i] < '!' || line[i] > '~')
			i ++;
		if ((line[i] > ' ' && line[i] < '0') || line[i] > '9')
			put_error("line is corrupted\n");
		tab[color] = color_calcul(line, &i);
		while (line[i] < '!' || line[i] > '~')
			i ++;
		i ++;
	}
	i -= 2;
	while (line[++i])
		if (i < ft_strlen(line) + 1
			&& ' ' < line[i] && line[i] < '~' + 1)
			put_error("line is corrupted\n");
	return (1);
}

void	str_exist(char *line, t_img **texts, int count_f, int count_c)
{
	int	count;

	count = count_f + count_c;
	if ((!ft_strncmp(EAST, line, ft_strlen(EAST)) && texts[0]->file)
		|| (!ft_strncmp(WEST, line, ft_strlen(WEST)) && texts[2]->file)
		|| (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && texts[1]->file)
		|| (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && texts[3]->file)
		|| count > 2)
		put_error("line duplicates\n");
	if (!ft_strncmp(EAST, line, ft_strlen(EAST)) && !texts[0]->file)
		texts[0]->file = ft_strdup(line + 1 + ft_strlen(WEST));
	if (!ft_strncmp(WEST, line, ft_strlen(WEST)) && !texts[2]->file)
		texts[2]->file = ft_strdup(line + 1 + ft_strlen(WEST));
	if (!ft_strncmp(NORTH, line, ft_strlen(NORTH)) && !texts[1]->file)
		texts[1]->file = ft_strdup(line + 1 + ft_strlen(NORTH));
	if (!ft_strncmp(SOUTH, line, ft_strlen(SOUTH)) && !texts[3]->file)
		texts[3]->file = ft_strdup(line + 1 + ft_strlen(SOUTH));
}

void	check_infos(t_cub3d *game, int count_c, int count_f)
{
	int	i;

	i = -1;
	while (++i < NB_DIR)
	{
		if (count_c < 1 || count_f < 1 || !game->textures[i]->file
			|| ft_strlen(game->textures[i]->file) <= ft_strlen(XPM))
			put_error("missing .xpm file(s) or color information(s)\n");
	}
}

void	get_file(t_cub3d *game, char *file)
{
	int		fd;
	int		count_f;
	int		count_c;
	char	*line;

	fd = open_fd(file);
	if (fd < 0)
		return ;
	count_f = 0;
	count_c = 0;
	line = get_next_line(fd);
	while (line)
	{
		str_exist(line, game->textures, count_f, count_c);
		if (line[0] == FLOOR)
			count_f += get_colour(game->floor, line);
		if (line[0] == CEILING)
			count_c += get_colour(game->sky, line);
		free(line);
		line = get_next_line(fd);
	}
	check_infos(game, count_c, count_f);
	close(fd);
}
