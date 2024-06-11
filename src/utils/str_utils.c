/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:02:51 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/11 22:22:20 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	res;

	res = 0;
	if (size > 0)
	{
		while (size > 1 && src[res])
		{
			dest[res] = src[res];
			res++;
			size--;
		}
		dest[res] = 0;
	}
	while (src[res] != 0)
	{
		res++;
	}
	return (res);
}*/

/*size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && *s != 0)
	{
		s++;
		len++;
	}
	return (len);
}*/

/*int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}*/

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j] != 0)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = 0;
	return (dest);
}

/*char	*ft_strdup(const char *s)
{
	char	*dest;
	int		dest_len;

	dest_len = ft_strlen(s);
	dest = malloc(sizeof(char) * (dest_len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, dest_len);
	return (dest);
}*/
