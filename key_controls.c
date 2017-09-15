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

#include "fractol.h"

void				exit_wolf3d(t_env *env, t_wolf *wolf)
{
	mlx_destroy_image(env->mlx, env->image);
	mlx_destroy_window(env->mlx, env->window);
	ft_memdel((void **)&wolf->map);
	exit(0);
}

void				movement_controls(t_env *env, int keycode)
{
	float c0s;
	float s1n;

	c0s = 1 / sqrt(1 + pow(wolf->slope, 2));
	s1n = wolf->slope / sqrt(1 + pow(wolf->slope, 2));
	if (keycode == KEY_W)
	{
		pos_x += 0.1 * c0s;
		pos_y += 0.1 * s1n;
	}
	// if (keycode == KEY_A)
	// 	env->x_displace -= (env->scale < 15) ? 1 : (0.05 / (env->scale / 1000));
	// if (keycode == KEY_S)
	// 	env->y_displace += (env->scale < 15) ? 1 : (0.05 / (env->scale / 1000));
	if (keycode == KEY_D)
	{
		pos_x -= 0.1 * c0s;
		pos_y -= 0.1 * s1n;
	}
}

int					key_controls(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit_wolf3d(env);
	movement_controls(env, keycode);
	// if (keycode == KEY_C)
	// 	env->color_inc += (env->color_inc > 100000) ? 20000 : 2000;
	// if (keycode == KEY_V)
	// 	env->color_inc -= (env->color_inc > 100000) ? 20000 : 2000;
	env->reinit = true;
	reinit(env);
	return (0);
}
