/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 16:49:09 by dgerard           #+#    #+#             */
/*   Updated: 2017/07/24 17:00:30 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				exit_wolf3d(t_env *env)
{
	mlx_destroy_image(env->mlx, env->image);
	mlx_destroy_window(env->mlx, env->window);
	ft_memdel((void **)&WOLF->map);
	exit(0);
}

void				movement_controls(t_env *env, int keycode)
{
	double	vector_x_tmp;
	double	fov_x_tmp;

	if (keycode == KEY_W && !(WOLF->map[(int)(WOLF->pos_y + WOLF->vector_y)] & (0b1 << (int)(WOLF->pos_x + WOLF->vector_x))))
	{
		WOLF->pos_x += WOLF->vector_x;
		WOLF->pos_y += WOLF->vector_y;
	}
	else if (keycode == KEY_S && !(WOLF->map[(int)(WOLF->pos_y - WOLF->vector_y)] & (0b1 << (int)(WOLF->pos_x - WOLF->vector_x))))
	{
		WOLF->pos_x -= WOLF->vector_x;
		WOLF->pos_y -= WOLF->vector_y;
	}
	else if (keycode == KEY_A)
	{
		vector_x_tmp = WOLF->vector_x;
		WOLF->vector_x = (WOLF->vector_x * cos(-0.2)) - (WOLF->vector_y * sin(-0.2));
		WOLF->vector_y = (vector_x_tmp * sin(-0.2)) + (WOLF->vector_y * cos(-0.2));
		fov_x_tmp = WOLF->fov_x;
		WOLF->fov_x = (WOLF->fov_x * cos(-0.2)) - (WOLF->fov_y * sin(-0.2));
		WOLF->fov_y = (fov_x_tmp * sin(-0.2)) + (WOLF->fov_y * cos(-0.2));
	}
	else if (keycode == KEY_D)
	{
		vector_x_tmp = WOLF->vector_x;
		WOLF->vector_x = (WOLF->vector_x * cos(0.2)) - (WOLF->vector_y * sin(0.2));
		WOLF->vector_y = (vector_x_tmp * sin(0.2)) + (WOLF->vector_y * cos(0.2));
		fov_x_tmp = WOLF->fov_x;
		WOLF->fov_x = (WOLF->fov_x * cos(0.2)) - (WOLF->fov_y * sin(0.2));
		WOLF->fov_y = (fov_x_tmp * sin(0.2)) + (WOLF->fov_y * cos(0.2));
	}
}

// void				rotation_controls(t_env *env, int keycode)
// {
// 	if (keycode == KEY_A)
// 	{
//
// 	}
// }
//

int					key_controls(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit_wolf3d(env);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		movement_controls(env, keycode);
	// if (keycode == KEY_O || keycode == KEY_P)
		// rotation_controls(env, keycode);
	env->reinit = true;
	reinit(env, env->wolf_mem);
	return (0);
}
