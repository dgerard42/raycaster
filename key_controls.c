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
	system("killall afplay");
	exit(0);
}

void				movement_controls(t_env *env, int keycode)
{
	if (keycode == KEY_W)
	{
		if (!(WOLF->map[(int)(WOLF->pos_y + (WOLF->vec_y * 1))] &
			(0b1 << (int)(WOLF->pos_x + (WOLF->vec_x * 1)))))
		{
			WOLF->pos_x += WOLF->vec_x * SPEED;
			WOLF->pos_y += WOLF->vec_y * SPEED;
		}
	}
	else if (keycode == KEY_S)
	{
		if (!(WOLF->map[(int)(WOLF->pos_y - (WOLF->vec_y * 1))] &
			(0b1 << (int)(WOLF->pos_x - (WOLF->vec_x * 1)))))
		{
			WOLF->pos_x -= WOLF->vec_x * SPEED;
			WOLF->pos_y -= WOLF->vec_y * SPEED;
		}
	}
}

void				rotation_controls(t_env *env, int keycode)
{
	double	vec_x_tmp;
	double	fov_x_tmp;

	if (keycode == KEY_D)
	{
		vec_x_tmp = WOLF->vec_x;
		WOLF->vec_x = (WOLF->vec_x * cos(-0.1)) - (WOLF->vec_y * sin(-0.1));
		WOLF->vec_y = (vec_x_tmp * sin(-0.1)) + (WOLF->vec_y * cos(-0.1));
		fov_x_tmp = WOLF->fov_x;
		WOLF->fov_x = (WOLF->fov_x * cos(-0.1)) - (WOLF->fov_y * sin(-0.1));
		WOLF->fov_y = (fov_x_tmp * sin(-0.1)) + (WOLF->fov_y * cos(-0.1));
	}
	else if (keycode == KEY_A)
	{
		vec_x_tmp = WOLF->vec_x;
		WOLF->vec_x = (WOLF->vec_x * cos(0.1)) - (WOLF->vec_y * sin(0.1));
		WOLF->vec_y = (vec_x_tmp * sin(0.1)) + (WOLF->vec_y * cos(0.1));
		fov_x_tmp = WOLF->fov_x;
		WOLF->fov_x = (WOLF->fov_x * cos(0.1)) - (WOLF->fov_y * sin(0.1));
		WOLF->fov_y = (fov_x_tmp * sin(0.1)) + (WOLF->fov_y * cos(0.1));
	}
}

int					key_controls(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit_wolf3d(env);
	else if (keycode == KEY_W || keycode == KEY_S)
		movement_controls(env, keycode);
	else if (keycode == KEY_D || keycode == KEY_A)
		rotation_controls(env, keycode);
	else if (keycode == KEY_M)
	{
		WOLF->minimap = (WOLF->minimap == true) ? false : true;
		if (WOLF->minimap == false)
			welcome_user();
	}
	env->reinit = true;
	reinit(env, env->wolf_mem);
	return (0);
}
