/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:25:39 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/10 17:25:48 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "cub3D.h"

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

void	*make_data(t_game *game, char *file, t_dep s)
{
	void	*data;
	int		fd;

	fd = open_fd(file);
	if (fd < 0)
		ft_close(1);
	close(fd);
	data = mlx_xpm_file_to_image(game->vars.mlx, file, &s.x, &s.y);
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

void	make_data_map(t_game *game)
{
	char	*file;
	t_dep	size;
	int		i;
	int		s;

	size = (t_dep){PIXS_BASE, PIXS_BASE};
	i = -1;
	while (++i < NB_DIR)
	{
		s = 0;
		while (41 > game->wall_files[i][s] || game->wall_files[i][s] > 127)
			s ++;
		file = ft_strdup(game->wall_files[i] + s);
		game->wall_img[i] = make_data(game, file, size);
		free(file);
	}
}
