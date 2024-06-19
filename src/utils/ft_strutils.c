/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:18:08 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:18:08 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((!dest || !src) && !n)
		return (i);
	if (!n)
		return (ft_strlen(src));
	while (i < (n - 1) && src[i])
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, char const *src, size_t n)
{
	size_t	i;
	size_t	dest_len;

	if ((!dest || !src) && !n)
		return (n);
	if (ft_strlen(dest) >= n)
		return (ft_strlen(src) + n);
	dest_len = ft_strlen(dest);
	i = dest_len - 1;
	while (++i < (n - 1) && src[i - dest_len])
		dest[i] = src[i - dest_len];
	dest[i] = '\0';
	if (n > dest_len)
		return (ft_strlen(src) + dest_len);
	else
		return (ft_strlen(src) + n);
}

char	*ft_strjoin(char const *str, char const *s)
{
	char	*comp_str;

	if (!str || !s)
		return (NULL);
	comp_str = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(s) + 1));
	if (!comp_str)
		return (NULL);
	ft_strlcpy(comp_str, str, ft_strlen(str) + 1);
	ft_strlcat(comp_str, s, ft_strlen(s) + ft_strlen(str) + 1);
	return (comp_str);
}

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < (n - 1) && s1[i] == s2[i])
		i++;
	if (!n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(char const *str)
{
	int	compt;

	compt = 0;
	while (str[compt] != '\0')
		compt ++;
	return (compt);
}
