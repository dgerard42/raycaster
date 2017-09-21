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
	// ft_memdel((void **)&wolf->map);
	ft_memdel((void **)&((t_wolf *)env->wolf_mem)->map);
	exit(0);
}

// void				movement_controls(t_env *env, int keycode)
// {
// 	float c0s;
// 	float s1n;
//
// 	if (keycode == KEY_W || keycode == KEY_S)
// 	{
// 		c0s = 1 / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->slope, 2));
// 		s1n = ((t_wolf *)env->wolf_mem)->slope / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->slope, 2));
// 		((t_wolf *)env->wolf_mem)->view_x -= ((t_wolf *)env->wolf_mem)->pos_x;//make this plus whatever angle ur at
// 		((t_wolf *)env->wolf_mem)->view_y -= ((t_wolf *)env->wolf_mem)->pos_y;
// 	}
// 	if (keycode == KEY_S)
// 	{
// 		((t_wolf *)env->wolf_mem)->pos_x += 0.01 * c0s;
// 		((t_wolf *)env->wolf_mem)->pos_y += 0.01 * s1n;
// 		// printf("%f, %f\n", ((t_wolf *)env->wolf_mem)->pos_x, ((t_wolf *)env->wolf_mem)->pos_y);
// 		((t_wolf *)env->wolf_mem)->view_x += ((t_wolf *)env->wolf_mem)->pos_x;//make this plus whatever angle ur at
// 		((t_wolf *)env->wolf_mem)->view_y += ((t_wolf *)env->wolf_mem)->pos_y;
// 	}
// 	if (keycode == KEY_W)
// 	{
// 		((t_wolf *)env->wolf_mem)->pos_x -= 0.001 * c0s;
// 		((t_wolf *)env->wolf_mem)->pos_y -= 0.001 * s1n;
// 		((t_wolf *)env->wolf_mem)->view_x += ((t_wolf *)env->wolf_mem)->pos_x;
// 		((t_wolf *)env->wolf_mem)->view_y += ((t_wolf *)env->wolf_mem)->pos_y;
// 	}
// 	// if (keycode == KEY_A)
// 	// {
// 	//
// 	// }
// }

void				movement_controls(t_env * env, int keycode)
{
	
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
	reinit(env, (t_wolf *)env->wolf_mem);
	return (0);
}
