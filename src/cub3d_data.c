/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:34:00 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:35:10 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*make_file(char *str1, char *str2, char *str3, char *str4)
{
	char	*str;

	str = NULL;
	str = ft_newstr(str, str1);
	str = ft_newstr(str, str2);
	str = ft_newstr(str, str3);
	str = ft_newstr(str, str4);
	if (str)
		str = ft_newstr(str, XPM);
	return (str);
}

void	*make_data(t_cub3d *game, char *file, int *x, int *y)
{
	void	*data;
	int		fd;

	fd = open_fd(file);
	if (fd < 0)
		ft_close(1);
	close(fd);
	data = mlx_xpm_file_to_image(game->mlx, file, x, y);
	if (!data)
	{
		if (!file)
			ft_putstr_fd("NULL", 1);
		else
			ft_putstr_fd(file, 1);
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd("while trying to create .xpm image\n", 1);
		ft_close(1);
	}
	return (data);
}

void	make_data_map(t_cub3d *game)
{
	char	*file;
	int		i;
	int		start;

	i = -1;
	while (++i < NB_DIR)
	{
		start = 0;
		while (41 > game->textures[i]->file[start]
			|| game->textures[i]->file[start] > 126)
			start ++;
		file = ft_strdup(game->textures[i]->file + start);
		while (file[ft_strlen(file) - 1] < '!'
			|| file[ft_strlen(file) - 1] > '~')
			file[ft_strlen(file) - 1] = '\0';
		game->textures[i]->img = make_data(game, file,
				&(game->textures[i]->width),
				&(game->textures[i]->height));
		free(file);
	}
	init_tex(game);
}
