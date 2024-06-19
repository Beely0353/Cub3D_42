/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:03:07 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/19 19:23:25 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_cub3d *cub)
{
	cub->key_states[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	cub->key_states[keycode] = 0;
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*tab;

	i = 0;
	tab = (void *)malloc(size * nmemb);
	if (!tab)
		return (NULL);
	while (i < nmemb * size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}
