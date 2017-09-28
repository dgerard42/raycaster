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
	// int	color;

	y = 0;
	wall_hi = WIN_HI / wolf->distance;
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

// void				shoot_ray(t_env *env, t_wolf *wolf)
// {
// 	//keep track of whole number map values to make sure that you arn't rounding down
// 	float	wall_x;
// 	float	wall_y;
// 	// int		map_x;
// 	// int		map_y;
//
// 	wall_x = wolf->pos_x;
// 	wall_y = wolf->pos_y;
// 	// map_x = (int)wolf->pos_x;
// 	// map_y = (int)wolf->pos_y;
// 	// printf("int(wall_x)@start%f\n", wall_x);
// 	// printf("int(wall_y)@start%f\n", wall_y);
// 	while (1)
// 	{
// 		// printf("map[%d][%d]\n", (int)wall_y, (int)wall_x);
// 		// if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))// (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << ((int)wall_x + 1))))
// 		// {
// 		// 	printf("case 0\n");
// 		// 	break;
// 		// }
// 		// else
// 		// {
// 		// 	printf("here\n");
// 		// 	wall_x -= wolf->inc_x;
// 		// 	printf("map[%d][%d]\n", (int)wall_y, (int)wall_x);
// 		// 	if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
// 		// 	{
// 		// 		printf("case 1\n");
// 		// 		break;
// 		// 	}
// 		// 	wall_x += wolf->inc_x;
// 		// }
// 		if (wolf->map[(int)wall_y] & (0b1 << ((int)wall_x + wolf->inc_x)))
// 		{
// 			printf("new break 0\n");
// 			wolf->side =
// 			break;
// 		}
// 		else if (wolf->map[(int)wall_y + wolf->inc_y] & (0b1 << (int)wall_x))
// 		{
// 			printf("new break 1\n");
// 			break;
// 		}
// 		if (((int)wall_y + wolf->inc_y) - wall_y < ((int)wall_x + wolf->inc_x) - wall_x)
// 		{
// 			wall_y = (int)wall_y + wolf->inc_y;
// 			wall_x = (wall_y - wolf->y_int) / wolf->slope;
// 			// map_y += wolf->inc_y;
// 			printf("y if wall_x%f, wall_y%f\n", wall_x, wall_y);
// 			if (wall_x > wolf->map_choice)
// 			{
// 				wall_x = wolf->map_choice;
// 				wall_y = (wolf->slope * wall_x) + wolf->y_int;
// 				printf("hit x max\n");
// 				break;
// 			}
// 			printf("y if wall_x%f, wall_y%f\n", wall_x, wall_y);
// 			if (wall_x < 0)
// 				wall_x = 0;
// 			// if (wolf->map[(int)wall_y - wolf->inc_y] & (0b1 << (int)wall_x))
// 				// break;
// 			// wolf->side = 0;
// 			// if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << ((int)wall_x + 1)))
// 				// break;
// 		}
// 		else
// 		{
// 			wall_x = (int)wall_x + wolf->inc_x;
// 			wall_y = (wolf->slope * wall_x) + wolf->y_int;
// 			// map_x += wolf->inc_x;
// 			printf("x else wall_x%f, wall_y%f\n", wall_x, wall_y);
// 			if (wall_y > 14)
// 			{
// 				wall_y = 14.0;
// 				wall_x = (wall_y - wolf->y_int) / wolf->slope;
// 				printf("hit y max\n");
// 				break;
// 			}
// 			printf("x else wall_x%f, wall_y%f\n", wall_x, wall_y);
// 			printf("incx%d, incy%d\n", wolf->inc_x, wolf->inc_y);
// 			if (wall_y < 0)
// 				wall_y = 0;
// 			// if (wolf->map[(int)wall_y] & (0b1 << ((int)wall_x - wolf->inc_x)))
// 				// break;
// 			// wolf->side = 1;
// 			// if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
// 				// break;
// 		}
// 		// printf("wall_x%f\n", wall_x);
// 		// printf("wolf->slope%f\n", wolf->slope);
// 		// printf("yint%f\n", wolf->y_int);
// 		// printf("wall_y%f\n", wall_y);
// 	}
// 	wolf->distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
// 	// printf("distance = %f\n", wolf->distance);
// }

void				shoot_yray(t_env *Env, t_wolf *wolf)
{
	int		wall_y;
	float	wall_x;
	float	distance;

	wall_y = (int)wolf->pos_y;
	wall_x = wolf->pos_x;
	while (1 && wolf->map[wall_y])
	{
		if (wolf->map[wall_y] & (0b1 << (int)wall_x))
			break;
		wall_y = wall_y + wolf->inc_y;
		wall_x = ((float)wall_y - wolf->y_int) / wolf->slope;
	}
	distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf((float)wall_y - wolf->pos_y, 2.0));
	if (distance < wolf->distance)
		wolf->distance = distance;
}

void				shoot_xray(t_env *env, t_wolf *wolf)
{
	int 	wall_x;
	float	wall_y;

	wall_y = wolf->pos_y;
	wall_x = (int)wolf->pos_x;
	while (1 && wolf->map[(int)wall_y])
	{
		if (wolf->map[(int)wall_y + wolf->inc_y] & (0b1 << wall_x))
			break;
		wall_x = wall_x + wolf->inc_x;
		wall_y = (wolf->slope * (float)wall_x) + wolf->y_int;
	}
	wolf->distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf((float)wall_y - wolf->pos_y, 2.0));
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
	wolf->view_x = wolf->pos_x + 0;
	wolf->view_y = wolf->pos_y + 1.5;
	// wolf->radians = ((float)3 / (float)2) * 3.14159;
	// printf("%f\n", wolf->radians);

}

void				raycaster(t_env *env, t_wolf *wolf)
{
	int		x;
	float	view_inc;
	float	tmp_viewx;

	x = 0;
	view_inc = (float)2 / ((float)WIN_LEN - (float)1 / (float)2);
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
	// printf("distance = %f\n", wolf->distance);
	wolf->view_x = tmp_viewx;
	// printf("wolf->view_x = %f\n", wolf->view_x);
}
