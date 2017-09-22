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

void				movement_controls(t_env *env, int keycode)
{
	float x_add;
	float y_add;

	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D)
	{
		x_add = 0.3 / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->slope, 2));
		y_add = (0.3 * ((t_wolf *)env->wolf_mem)->slope) / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->slope, 2));
	}
	if (keycode == KEY_W)
	{
		// printf("xadd%f\n", x_add);
		// printf("yadd%f\n", y_add);
		((t_wolf *)env->wolf_mem)->pos_x += x_add;
		((t_wolf *)env->wolf_mem)->pos_y += y_add;
		((t_wolf *)env->wolf_mem)->view_x += x_add;
		((t_wolf *)env->wolf_mem)->view_y += y_add;
		// printf("%f, %f\n", ((t_wolf *)env->wolf_mem)->pos_x, ((t_wolf *)env->wolf_mem)->pos_y);
	}
	else if (keycode == KEY_S)
	{
		// printf("xadd%f\n", x_add);
		// printf("yadd%f\n", y_add);
		((t_wolf *)env->wolf_mem)->pos_x -= x_add;
		((t_wolf *)env->wolf_mem)->pos_y -= y_add;
		((t_wolf *)env->wolf_mem)->view_x -= x_add;
		((t_wolf *)env->wolf_mem)->view_y -= y_add;
		// printf("%f, %f\n", ((t_wolf *)env->wolf_mem)->pos_x, ((t_wolf *)env->wolf_mem)->pos_y);
	}
	else if (keycode == KEY_A)
	{
		((t_wolf *)env->wolf_mem)->pos_x += y_add;
		((t_wolf *)env->wolf_mem)->pos_y += x_add;
		((t_wolf *)env->wolf_mem)->view_x += y_add;
		((t_wolf *)env->wolf_mem)->view_y += x_add;
	}
	else if (keycode == KEY_D)
	{
		((t_wolf *)env->wolf_mem)->pos_x -= y_add;
		((t_wolf *)env->wolf_mem)->pos_y -= x_add;
		((t_wolf *)env->wolf_mem)->view_x -= y_add;
		((t_wolf *)env->wolf_mem)->view_y -= x_add;
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
	reinit(env, (t_wolf *)env->wolf_mem);
	return (0);
}
