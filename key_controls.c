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

}

void				rotation_controls(t_env *env, int keycode)
{
	
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
