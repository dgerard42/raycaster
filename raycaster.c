/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 15:15:31 by dgerard           #+#    #+#             */
/*   Updated: 2017/09/27 10:05:25 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// int					wall_color(t_wolf *wolf)
// {
// 	float rise;
// 	float run;
//
// 	rise = (wolf->view_y - wolf->map_choice) - (wolf->pos_y - wolf->map_choice);
// 	run = (wolf->view_x - 15) - (wolf->pos_x - 15);
// 	if (run <= 1 && run >= -1 && rise >= 1)
// 		return (0x580202);
// 	else if (rise <= 1 && rise >= -1 && run >= 1)
// 		return (0x603434);
// 	else if (run <= 1 && run >= -1 && rise <= 1)
// 		return (0x545252);
// 	else if (rise <= 1 && rise >= -1 && run <= 1)
// 		return(0xbf1a1a);
// 	else
// 		return (0x00FF00); //error color
// }

void				draw_wall(t_env *env, t_wolf *wolf, int x)
{
	int y;
	int	sky;
	int	wall_hi;
	int	color;//0x580202

	y = 0;
	if (wolf->distance == 0)
		wall_hi = WIN_HI - 2;
	else
		wall_hi = WIN_HI / wolf->distance;
	if (0x0000FF - (wolf->distance * 12) > 0x000000)
		color = 0x0000FF - (wolf->distance * 12);
	else
		color = 0x000000;
	if (wolf->side == 1 && color - 32 > 0x000000)
		color -= 32;
	sky = (WIN_HI - wall_hi) / 2;
	// ft_printf("sky = %d\n", sky);
	// color = wall_color(wolf);
	while (y < sky)
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x000000;
		// printf("~~~inf here\n");
	}
	while (wall_hi-- > 0)
	{
		env->pixels[x + (y++ * WIN_LEN)] = color;
		// printf("~~~inf here\n");
	}
	while (y < (WIN_HI - 1))
	{
		env->pixels[x + (y++ * WIN_LEN)] = 0x000000;
		// printf("~~~inf here\n");
	}
	// printf("line of wall drawn %d\n", x);
}

void				shoot_yray(t_env *env, t_wolf *wolf)
{
	float	wall_y;
	float	wall_x;
	float	distance;

	wall_y = wolf->pos_y;
	wall_x = wolf->pos_x;
	// wall_y = wolf->pos_y + wolf->inc_y;
	// wall_x = (wall_y - wolf->y_int) / wolf->slope;
	while (1 && wolf->map[(int)wall_y])
	{
		// if (wolf->map[(int)wall_y + wolf->inc_y] & (0b1 << ((int)wall_x + wolf->inc_x)))
			// break;
		// if (wolf->map[(int)wall_y + wolf->inc_y] & (0b1 << ((int)wall_x - 0)))
			// break; //best version so far, but it doesn't connect walls
		if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
			break; //no incs
		wall_y = (int)wall_y + wolf->inc_y;
		wall_x = (wall_y - wolf->y_int) / wolf->slope;
		if (wall_x > wolf->map_choice)
			wall_x = wolf->map_choice;
		if (wall_x < 0)
			wall_x = 0;
	}
	// distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
	distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
	// distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y - wolf->inc_y, 2.0));
	if (distance < wolf->distance)
	{
		wolf->distance = distance;
		wolf->side = 1;
	}
}

void				shoot_xray(t_env *env, t_wolf *wolf)
{
	float 	wall_x;
	float	wall_y;

	wall_x = wolf->pos_x;
	// wall_x = wolf->pos_x + wolf->inc_x;
	wall_y = wolf->pos_y;
	// wall_y = (wolf->slope * wall_x) + wolf->y_int;
	while (1 && wolf->map[(int)wall_y])
	{
		// if (wolf->map[(int)wall_y + wolf->inc_y] & (0b1 << ((int)wall_x + wolf->inc_x)))
			// break;

		// if (wolf->map[(int)wall_y] & (0b1 << ((int)wall_x + wolf->inc_x)))
			// break; //best version
		if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
			break; //no incs
		wall_x = (int)wall_x + wolf->inc_x; //typecasting as an int here allows an even increment to the next whole # from a possible decimaled starting point
		wall_y = (wolf->slope * wall_x) + wolf->y_int;
		if (wall_y > 14.0)
			wall_y = 14.0;
		if (wall_y < 0)
			wall_y = 0;
	}
	wolf->distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
	wolf->side = 0;
	// printf("wall_x%f\n", wall_x);
	// printf("wall_y%f\n", wall_y);
	// wolf->distance = sqrt(powf(wall_x - wolf->pos_x - wolf->inc_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
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
	wolf->pos_x = 3;
	wolf->pos_y = 4;
	wolf->view_x = wolf->pos_x + 0;
	wolf->view_y = wolf->pos_y + 1;
	wolf->radians = (3 * M_PI) / 2;
	// wolf->radians = ((float)3 / (float)2) * 3.14159;
	// printf("%f\n", wolf->radians);

}

void				raycaster(t_env *env, t_wolf *wolf)
{
	int		x;
	float	view_inc;
	float	tmp_viewx;

	x = 0;
	view_inc = (float)1.5 / ((float)WIN_LEN - (float)1 / (float)2);
	if (env->reinit == false)
		initialize(env, wolf);
	// printf("%f\n", view_inc);
	// printf("posy%f\n", wolf->pos_y);
	// printf("posx%f\n", wolf->pos_x);
	// printf("view_y%f\n", wolf->view_y);
	// printf("wolf->view_x%f\n", wolf->view_x);
	tmp_viewx = wolf->view_x;
	wolf->rise = wolf->view_y - wolf->pos_y;
	wolf->run = wolf->view_x - wolf->pos_x;
	wolf->view_x -= view_inc * ((WIN_LEN - 1) / 2);
	while (x < (WIN_LEN - 1))
	{
		// ft_printf("seg0\n");
		// rotation(wolf);
		wolf->slope = (wolf->view_x - wolf->pos_x == 0) ? wolf->rise / 0.0001 : wolf->rise / (wolf->view_x - wolf->pos_x);
		// wolf->inv_slope = -((wolf->view_x - wolf->pos_x) / (wolf->view_y - wolf->pos_y));
		// printf("slope%f\n", wolf->slope);
		// printf("slope%f\n", wolf->inv_slope);
		wolf->inc_x = (wolf->view_x - wolf->pos_x > 0) ? 1 : -1;
		wolf->inc_y = (wolf->view_y - wolf->pos_y > 0) ? 1 : -1;
		// printf("incx%d, incy%d\n", wolf->inc_x, wolf->inc_y);
		// printf("posy%f\n", wolf->pos_y);
		// printf("posx%f\n", wolf->pos_x);
		// printf("view_y%f\n", wolf->view_y);
		// printf("view_x%f\n", wolf->view_x);
		// printf("viewy - posy = %f\n", wolf->view_y - wolf->pos_y);
		// printf("viewx - posx = %f\n", wolf->view_x - wolf->pos_x);
		wolf->y_int = -(wolf->slope * wolf->pos_x) + wolf->pos_y;
		// ft_printf("seg2\n");
		shoot_xray(env, wolf);
		shoot_yray(env, wolf);
		// ft_printf("seg3\n");
		draw_wall(env, wolf, x);
		// ft_printf("%d\n", x);
		x++;
		wolf->view_x += view_inc;
	}
	printf("wolf->dist %f\n", wolf->distance);
	// printf("distance = %f\n", wolf->distance);
	wolf->view_x = tmp_viewx;
	// printf("wolf->view_x = %f\n", wolf->view_x);
}
