/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 15:15:31 by dgerard           #+#    #+#             */
/*   Updated: 2017/08/28 15:15:32 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				shoot_ray(t_wolf *wolf, float slope, float y_int)
{
	float	wall_x;
	float	wall_y;

	wall_x = wolf->pos_x;
	wall_y = wolf->pos_y;
	while (1)
	{
		if (((int)wall_y + 1) - wolf->pos_y < ((int)wall_x + 1) - wolf->pos_x)
		{
			wall_y = (int)wall_y + 1;
			wall_x = (wall_y- y_int) / slope;
			if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break;
		}
		else
		{
			wall_x = (int)wall_x + 1;
			wall_y = (slope * wall_x) + y_int;
			if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break;
		}
	}
	wolf->distance = sqrt(ft_power(wall_x - wolf->pos_x, 2) + ft_power(wall_y - wolf->pos_y, 2));
}

void				draw_wall(t_env *env, t_wolf *wolf)
{
	int y;
	int	sky;
	int	wall_hi;

	y = 0;
	wall_hi = WIN_HI - ((int)wolf->distance * 200);
	sky = (WIN_HI - wall_hi) / 2;
	ft_printf("seghere3\n");
	while (y < sky)
	{
		env->pixels[(int)wolf->view_x + (y++ * WIN_LEN)] = 0x010022;
		// printf("seghere4\n");
	}
	while (y + sky < WIN_HI)
	{
		env->pixels[(int)wolf->view_x + (y++ * WIN_LEN)] = 0x004212;
		printf("wolf->distance%f\n", wolf->distance);
		// printf("seghere5\n");
	}
	while (y < WIN_HI - 1)
	{
		env->pixels[(int)wolf->view_x + (y++ * WIN_LEN)] = 0x241400;
		// printf("seghere6\n");
	}
}

void				initialize(t_env * env, t_wolf *wolf)
{
	if (env->reinit == false)
	{
		wolf->pos_x = 1;
		wolf->pos_y = 1;
		// make sure that if its a blocked area that you can't spawn there
		wolf->view_x = wolf->pos_x + 1;
		wolf->view_y = wolf->pos_y + 1;
	}
}

void				raycaster(t_env *env, t_wolf *wolf)
{
	int		x;
	float	slope;
	float	y_int;

	initialize(env, wolf);
	ft_printf("seghere0\n");
	slope = (wolf->view_y - wolf->pos_y) / (wolf->view_x - wolf->pos_x);
	y_int = -(slope * wolf->pos_x) + wolf->pos_y;
	wolf->view_x = wolf->view_x - (wolf->view_x / 2);
	while (x++ < (WIN_LEN - 1))
	{
		// printf("seghere1\n");
		shoot_ray(wolf, slope, y_int);
		// printf("seghere2\n");
		wolf->view_x++;
		draw_wall(env, wolf);
	}
	wolf->view_x = wolf->view_x * 2;
}
