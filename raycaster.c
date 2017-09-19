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

void				draw_wall(t_env *env, t_wolf *wolf, int x)
{
	int y;
	int	sky;
	int	wall_hi;

	y = 0;
	wall_hi = WIN_HI - ((int)wolf->distance * 200);
	sky = (WIN_HI - wall_hi) / 2;
	while (y < sky)
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x010022;
		printf("seghere4\n");
	}
//	while (y + (sky * 2) < WIN_HI)
	while (wall_hi-- > 0)
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x004212;
		printf("seghere5\n");
	}
	while (y < WIN_HI - 1)
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x241400;
		printf("seghere6\n");
	}
	// printf("wolf->view_x = %f, y = %d\n", wolf->view_x, y);
}

void				shoot_ray(t_env *env, t_wolf *wolf)
{
	float	wall_x;
	float	wall_y;

	wall_x = wolf->pos_x;
	wall_y = wolf->pos_y;
	printf("wat\n");
	while (1)
	{
		if (((int)wall_y + 1) - wolf->pos_y < ((int)wall_x + 1) - wolf->pos_x)
		{
			wall_y = (int)wall_y + 1;
			wall_x = (wall_y - wolf->y_int) / wolf->slope;
			printf("the\n");
			if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break;
		}
		else
		{
			wall_x = (int)wall_x + 1;
			printf("int(wall_x)%f\n", wall_x);
			printf("wolf->slope%f\n", wolf->slope);
			printf("yint%f\n", wolf->y_int);
			printf("int(wall_y)%d\n", (int)wall_y);
			wall_y = (wolf->slope * wall_x) + wolf->y_int;
			printf("int(wall_y)%d\n", (int)wall_y);
			if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break;
			printf("fug\n");
		}
	}
	wolf->distance = sqrt(ft_power(wall_x - wolf->pos_x, 2) + ft_power(wall_y - wolf->pos_y, 2));
	printf("distance = %f\n", wolf->distance);
//	wolf->view_x++;
//	draw_wall(env, wolf);
}

void				initialize(t_env * env, t_wolf *wolf)
{
	int x;
	int y;

	y = 0;
	while (y < 15) //&& wolf->map[y] & 0b1 << x)
	{
		x = 0;
		while (x < wolf->map_choice)//&& wolf->map[y] & 0b1 << x)
		{
			if (!(wolf->map[y] & 0b1 << x))
				break;
			x++;
		}
		if (!(wolf->map[y] & 0b1 << x))
			break;
		y++;
	}
	printf("x%d, y%d\n", x, y);
	wolf->pos_x = (float)x;
	wolf->pos_y = (float)y;
	wolf->view_x = wolf->pos_x + 1;
	wolf->view_y = wolf->pos_y + 1;
}

void				raycaster(t_env *env, t_wolf *wolf)
{
	int		x;

	x = 0;
	if (env->reinit == false)
		initialize(env, wolf);
	wolf->view_x -= 1;
	while (x < (WIN_LEN - 1))
	{
		printf("seg0\n");
		wolf->slope = (wolf->view_y - wolf->pos_y) / (wolf->view_x - wolf->pos_x);
		printf("seg1\n");
		wolf->y_int = -(wolf->slope * wolf->pos_x) + wolf->pos_y;
		printf("seg2\n");
		shoot_ray(env, wolf);
		printf("seg3\n");
		draw_wall(env, wolf, x);
		printf("%d\n", x);
		x++;
		wolf->view_x += 2 / (WIN_LEN - 1);
	}
	wolf->view_x -= 1;
	printf("wolf->view_x = %f\n", wolf->view_x);
}
