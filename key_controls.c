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
	ft_memdel((void **)&((t_wolf *)env->wolf_mem)->map);
	exit(0);
}

void				movement_controls(t_env *env, int keycode)
{
	float x_add;
	float y_add;

	if (keycode == KEY_W || keycode == KEY_S)
	{
		// x_add = 0.2 / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->slope, 2));
		// y_add = (0.2 * ((t_wolf *)env->wolf_mem)->slope) / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->slope, 2));
		x_add = ((t_wolf *)env->wolf_mem)->run / 8;
		y_add = ((t_wolf *)env->wolf_mem)->rise / 8;
	}
	else if (keycode == KEY_A || keycode == KEY_D)
	{
		// x_add = -0.2 / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->inv_slope, 2));
		// y_add = (-0.2 * ((t_wolf *)env->wolf_mem)->inv_slope) / sqrt(1 + pow(((t_wolf *)env->wolf_mem)->inv_slope, 2));
		x_add = ((t_wolf *)env->wolf_mem)->rise / 8;
		y_add = ((t_wolf *)env->wolf_mem)->run / 8;
	}
	// printf("xadd%f\n", x_add);
	// printf("yadd%f\n", y_add);
	if (keycode == KEY_W)
	{
		((t_wolf *)env->wolf_mem)->pos_x += x_add;
		((t_wolf *)env->wolf_mem)->pos_y += y_add;
		((t_wolf *)env->wolf_mem)->view_x += x_add;
		((t_wolf *)env->wolf_mem)->view_y += y_add;
		// printf("%f, %f\n", ((t_wolf *)env->wolf_mem)->pos_x, ((t_wolf *)env->wolf_mem)->pos_y);
	}
	else if (keycode == KEY_S)
	{
		((t_wolf *)env->wolf_mem)->pos_x -= x_add;
		((t_wolf *)env->wolf_mem)->pos_y -= y_add;
		((t_wolf *)env->wolf_mem)->view_x -= x_add;
		((t_wolf *)env->wolf_mem)->view_y -= y_add;
		// printf("%f, %f\n", ((t_wolf *)env->wolf_mem)->pos_x, ((t_wolf *)env->wolf_mem)->pos_y);
	}
	else if (keycode == KEY_A)
	{
		((t_wolf *)env->wolf_mem)->pos_x -= x_add;
		((t_wolf *)env->wolf_mem)->pos_y -= y_add;
		((t_wolf *)env->wolf_mem)->view_x -= x_add;
		((t_wolf *)env->wolf_mem)->view_y -= y_add;
	}
	else if (keycode == KEY_D)
	{
		((t_wolf *)env->wolf_mem)->pos_x += x_add;
		((t_wolf *)env->wolf_mem)->pos_y += y_add;
		((t_wolf *)env->wolf_mem)->view_x += x_add;
		((t_wolf *)env->wolf_mem)->view_y += y_add;
	}
}

void				rotation_controls(t_env *env, int keycode)
{
	float tmp_viewx;

	((t_wolf *)env->wolf_mem)->view_x -= ((t_wolf *)env->wolf_mem)->pos_x;
	((t_wolf *)env->wolf_mem)->view_y -= ((t_wolf *)env->wolf_mem)->pos_y;
	tmp_viewx = ((t_wolf *)env->wolf_mem)->view_x;
	if (keycode == KEY_O)
	{
		((t_wolf *)env->wolf_mem)->view_x = (tmp_viewx * cos(.2)) - (((t_wolf *)env->wolf_mem)->view_y * sin(.2));
		((t_wolf *)env->wolf_mem)->view_y = (tmp_viewx * sin(.2)) + (((t_wolf *)env->wolf_mem)->view_y * cos(.2));
		((t_wolf *)env->wolf_mem)->radians += 0.2;
	}
	else if (keycode == KEY_P)
	{
		((t_wolf *)env->wolf_mem)->view_x = (tmp_viewx * cos(-.2)) - (((t_wolf *)env->wolf_mem)->view_y * sin(-.2));
		((t_wolf *)env->wolf_mem)->view_y = (tmp_viewx * sin(-.2)) + (((t_wolf *)env->wolf_mem)->view_y * cos(-.2));
		((t_wolf *)env->wolf_mem)->radians -= 0.2;
	}
	((t_wolf *)env->wolf_mem)->view_x += ((t_wolf *)env->wolf_mem)->pos_x;
	((t_wolf *)env->wolf_mem)->view_y += ((t_wolf *)env->wolf_mem)->pos_y;
}


int					key_controls(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit_wolf3d(env);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		movement_controls(env, keycode);
	if (keycode == KEY_O || keycode == KEY_P)
		rotation_controls(env, keycode);
	env->reinit = true;
	reinit(env, (t_wolf *)env->wolf_mem);
	return (0);
}
