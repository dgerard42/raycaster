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
	wall_hi = WIN_HI / wolf->distance;
	sky = (WIN_HI - wall_hi) / 2;
	// ft_printf("sky = %d\n", sky);
	while (y < sky)
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x000000;
		// printf("~~~inf here\n");
	}
	while (wall_hi-- > 0)
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x580202;
		// printf("~~~inf here\n");
	}
	while (y < (WIN_HI - 1))
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x2d0e0e;
		// printf("~~~inf here\n");
	}
	// printf("line of wall drawn %d\n", x);
}

void				shoot_ray(t_env *env, t_wolf *wolf)
{
	float	wall_x;
	float	wall_y;

	wall_x = wolf->pos_x;
	wall_y = wolf->pos_y;
	// printf("int(wall_x)@start%f\n", wall_x);
	// printf("int(wall_y)@start%f\n", wall_y);
	while (1)
	{
		if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break;
		if (((int)wall_y + wolf->inc_y) - wolf->pos_y < ((int)wall_x + wolf->inc_x) - wolf->pos_x)
		{
			wall_y = (int)wall_y + wolf->inc_y;
			wall_x = (wall_y - wolf->y_int) / wolf->slope;
			if (wall_x > wolf->map_choice)
				wall_x = wolf->map_choice;
		}
		else
		{
			wall_x = (int)wall_x + wolf->inc_x;
			wall_y = (wolf->slope * wall_x) + wolf->y_int;
			if (wall_y > 14)
				wall_y = 14;
			// if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
			// 	break;
		}
		// printf("int(wall_x)%f\n", wall_x);
		// printf("wolf->slope%f\n", wolf->slope);
		// printf("yint%f\n", wolf->y_int);
		// printf("int(wall_y)%f\n", wal_y);
	}
	wolf->distance = sqrt(ft_power(wall_x - wolf->pos_x, 2) + ft_power(wall_y - wolf->pos_y, 2));
	// printf("distance = %f\n", wolf->distance);
}

void				initialize(t_env * env, t_wolf *wolf) //make this function less ugly when eveything works
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
	// printf("x%d, y%d\n", x, y);
	wolf->pos_x = (float)x;
	wolf->pos_y = (float)y;
	wolf->view_x = wolf->pos_x + 1;
	wolf->view_y = wolf->pos_y + 1;
}

void				raycaster(t_env *env, t_wolf *wolf)
{
	int		x;
	float	view_inc;

	x = 0;
	view_inc = (float)2 / ((float)WIN_LEN - (float)1 / (float)2);
	if (env->reinit == false)
		initialize(env, wolf);
	// printf("%f\n", view_inc);
	// printf("posy%f\n", wolf->pos_y);
	// printf("posx%f\n", wolf->pos_x);
	// printf("view_y%f\n", wolf->view_y);
	// printf("wolf->view_x%f\n", wolf->view_x);
	wolf->view_x -= view_inc * ((WIN_LEN - 1) / 2);
	while (x < (WIN_LEN - 1))
	{
		// ft_printf("seg0\n");
		wolf->slope = (wolf->view_y - wolf->pos_y) / (wolf->view_x - wolf->pos_x);
		// wolf->inv_slope = (wolf->view_x - wolf->pos_x) / (wolf->view_y - wolf->pos_y);
		wolf->inc_x = (wolf->view_x - wolf->pos_x > 0) ? 1 : -1;
		wolf->inc_y = (wolf->view_y - wolf->pos_y > 0) ? 1 : -1;
		// printf("posy%f\n", wolf->pos_y);
		// printf("posx%f\n", wolf->pos_x);
		// printf("view_y%f\n", wolf->view_y);
		// printf("view_x%f\n", wolf->view_x);
		// printf("viewy - posy = %f\n", wolf->view_y - wolf->pos_y);
		// printf("viewx - posx = %f\n", wolf->view_x - wolf->pos_x);
		wolf->y_int = -(wolf->slope * wolf->pos_x) + wolf->pos_y;
		// ft_printf("seg2\n");
		shoot_ray(env, wolf);
		// ft_printf("seg3\n");
		draw_wall(env, wolf, x);
		// ft_printf("%d\n", x);
		x++;
		wolf->view_x += view_inc;
	}
	wolf->view_x -= view_inc * (WIN_LEN / 2);
	// printf("wolf->view_x = %f\n", wolf->view_x);
}
