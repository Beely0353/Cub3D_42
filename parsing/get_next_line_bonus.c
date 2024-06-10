/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbigourd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 00:21:05 by hbigourd          #+#    #+#             */
/*   Updated: 2023/07/07 10:07:00 by hbigourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"
#include "get_next_line_bonus.h"

#define OPEN_MAX 500

char	*ft_newstr(char *str, char *to_join)
{
	char	*tmp;

	if (!to_join)
		return (str);
	if (!str)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(to_join) + 1));
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, to_join, ft_strlen(to_join) + 1);
	}
	else
	{
		tmp = ft_strjoin(str, to_join);
		free(str);
	}
	return (tmp);
}

char	*get_str(int fd, char *str)
{
	char	buff[BUFFER_SIZE + 1];
	int		rdb;
	int		i;

	rdb = 1;
	while (rdb)
	{
		rdb = read(fd, buff, BUFFER_SIZE);
		if (rdb < 0)
		{
			free(str);
			return (NULL);
		}
		buff[rdb] = '\0';
		str = ft_newstr(str, buff);
		if (!str)
			return (NULL);
		i = -1;
		while (buff[++i])
			if (buff[i] == '\n' || rdb < BUFFER_SIZE)
				return (str);
	}
	return (str);
}

char	*gnl_algo(char *str, char *leftrd)
{
	size_t	i;

	if (!*str)
	{
		free(str);
		while (ft_strlen(leftrd) > 0)
			leftrd[ft_strlen(leftrd) - 1] = '\0';
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] != '\n')
		i ++;
	if (str[i] != '\0')
		ft_strlcpy(leftrd, str + i + 1, ft_strlen(str + i + 1) + 1);
	if (str[i] != '\0')
		ft_strlcpy(str, str, i + 2);
	return (str);
}

char	*get_next_line(int fd)
{
	size_t		i;
	static char	leftrd[OPEN_MAX + 1][BUFFER_SIZE + 1];
	char		*str;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	str = ft_newstr(NULL, leftrd[fd]);
	ft_strlcpy(leftrd[fd], "", 1);
	i = 0;
	while (str[i] && str[i] != '\n')
		i ++;
	if (str[i] != '\n')
		str = get_str(fd, str);
	if (!str)
		return (NULL);
	return (gnl_algo(str, leftrd[fd]));
}
