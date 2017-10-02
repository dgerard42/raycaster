/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 15:05:31 by dgerard           #+#    #+#             */
/*   Updated: 2017/10/01 15:05:34 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void					draw_wall(t_env *env, t_wolf *wolf)
{

}

void					shoot_ray(t_env *env, t_wolf *wolf)
{
	double	wall_x;
	double	wall_y;

	while ()

}

void					ray_init(t_env *env, t_wolf *wolf)
{
	int x;
	int y;

	y = 0;
	while (y < 15) //make this nested loop better when everything else works
	{
		x = 0;
		while (x < wolf->map_choice)
		{
			if (!(wolf->map[y] & 0b1 << x))
				break;
			x++;
		}
		if (!(wolf->map[y] & 0b1 << x))
			break;
		y++;
	}
	// printf("x%d, y%d\n", x, y);
	// wolf->pos_x = x * SCALE; //revert all values to int and use scale AFTER u have it working
	// wolf->pos_y = y * SCALE;
	wolf->pos_x = x;
	wolf->pos_y = y;
	wolf->view_y = wolf->pos_y - 0;
}

void					raycaster(t_env, *env, t_wolf *wolf)
{
	int pixel;

	pixel = 0;
	if (env->reinit == false)
		ray_init(env, wolf);
	while (pixel < (WIN_LEN - 1))
	{
		shoot_ray(env, wolf);
		draw_wall(env, wolf);
		pixel++;
	}
}
