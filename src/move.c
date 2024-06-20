/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:14:41 by biaroun           #+#    #+#             */
/*   Updated: 2024/06/20 18:57:19 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward_backward(t_cub3d *cub)
{
	if (cub->key_states[KEY_Z])
	{
		cub->m = 1;
		if (cub->map[(int)floor(cub->p_pos[0] + cub->p_dir[0] * MOVEMENT)] \
		[(int)floor(cub->p_pos[1])] != '1')
			cub->p_pos[0] = cub->p_pos[0] + cub->p_dir[0] * MOVEMENT;
		if (cub->map[(int)floor(cub->p_pos[0])] \
		[(int)floor(cub->p_pos[1] + cub->p_dir[1] * MOVEMENT)] != '1')
			cub->p_pos[1] += cub->p_dir[1] * MOVEMENT;
	}
	if (cub->key_states[KEY_S])
	{
		cub->m = 1;
		if (cub->map[(int)floor(cub->p_pos[0] - cub->p_dir[0] * MOVEMENT)] \
		[(int)floor(cub->p_pos[1])] != '1')
			cub->p_pos[0] -= cub->p_dir[0] * MOVEMENT;
		if (cub->map[(int)floor(cub->p_pos[0])] \
		[(int)floor(cub->p_pos[1] - cub->p_dir[1] * MOVEMENT)] != '1')
			cub->p_pos[1] -= cub->p_dir[1] * MOVEMENT;
	}
}

void	right_left(t_cub3d *cub)
{
	if (cub->key_states[KEY_Q])
	{
		cub->m = 1;
		if (cub->map[(int)floor(cub->p_pos[0])] \
		[(int)floor(cub->p_pos[1] - cub->p_fov[1] * MOVEMENT)] != '1')
			cub->p_pos[1] -= cub->p_fov[1] * MOVEMENT;
		if (cub->map[(int)floor(cub->p_pos[0] - cub->p_fov[0] * MOVEMENT)] \
		[(int)floor(cub->p_pos[1])] != '1')
			cub->p_pos[0] -= cub->p_fov[0] * MOVEMENT;
	}
	if (cub->key_states[KEY_D])
	{
		cub->m = 1;
		if (cub->map[(int)floor(cub->p_pos[0])] \
		[(int)floor(cub->p_pos[1] + cub->p_fov[1] * MOVEMENT)] != '1')
			cub->p_pos[1] += cub->p_fov[1] * MOVEMENT;
		if (cub->map[(int)floor(cub->p_pos[0] + cub->p_fov[0] * MOVEMENT)] \
		[(int)floor(cub->p_pos[1])] != '1')
			cub->p_pos[0] += cub->p_fov[0] * MOVEMENT;
	}
}

void	turn_right(t_cub3d *cub)
{
	if (cub->key_states[KEY_RIGHT])
	{
		cub->m = 1;
		cub->p_old_dir = cub->p_dir[0];
		cub->p_dir[0] = cub->p_dir[0] * cos(-ROTATION * cub->p_rota) - \
		cub->p_dir[1] * sin(-ROTATION * cub->p_rota);
		cub->p_dir[1] = cub->p_old_dir * sin(-ROTATION * cub->p_rota) + \
		cub->p_dir[1] * cos(-ROTATION * cub->p_rota);
		cub->p_old_fov = cub->p_fov[0];
		cub->p_fov[0] = cub->p_fov[0] * cos(-ROTATION * cub->p_rota) - \
		cub->p_fov[1] * sin(-ROTATION * cub->p_rota);
		cub->p_fov[1] = cub->p_old_fov * sin(-ROTATION * cub->p_rota) + \
		cub->p_fov[1] * cos(-ROTATION * cub->p_rota);
	}
}

void	turn_left(t_cub3d *cub)
{
	if (cub->key_states[KEY_LEFT])
	{
		cub->m = 1;
		cub->p_old_dir = cub->p_dir[0];
		cub->p_dir[0] = cub->p_dir[0] * cos(ROTATION * cub->p_rota) - \
		cub->p_dir[1] * sin(ROTATION * cub->p_rota);
		cub->p_dir[1] = cub->p_old_dir * sin(ROTATION * cub->p_rota) + \
		cub->p_dir[1] * cos(ROTATION * cub->p_rota);
		cub->p_old_fov = cub->p_fov[0];
		cub->p_fov[0] = cub->p_fov[0] * cos(ROTATION * cub->p_rota) - \
		cub->p_fov[1] * sin(ROTATION * cub->p_rota);
		cub->p_fov[1] = cub->p_old_fov * sin(ROTATION * cub->p_rota) + \
		cub->p_fov[1] * cos(ROTATION * cub->p_rota);
	}
}

void	move_player(t_cub3d *cub)
{
	if (cub->key_states[KEY_ESC])
		exit(1);
	forward_backward(cub);
	right_left(cub);
	turn_right(cub);
	turn_left(cub);
	mlx_clear_window(cub->mlx, cub->win);
	raycasting(cub);
}
