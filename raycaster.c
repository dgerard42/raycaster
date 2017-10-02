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


void					draw_wall(t_env *env, t_wolf *wolf, int pixel)
{
	int y;
	int	sky;
	int	wall_hi;
	int	color;

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
	while (y < sky)
		env->pixels[pixel + (y++ * WIN_LEN)] = 0x000000;
	while (wall_hi-- > 0)
		env->pixels[pixel + (y++ * WIN_LEN)] = color;
	while (y < (WIN_HI - 1))
		env->pixels[pixel + (y++ * WIN_LEN)] = 0x000000;
}

void					shoot_ray(t_env *env, t_wolf *wolf)
{
	double	wall_x;
	double	wall_y;

	wall_x = wolf->pos_x;
	wall_y = wolf->pos_y;
	while (1 && wolf->map[(int)wall_y])
	{
		if (((int)wall_y + 1) - wolf->pos_y < ((int)wall_x + 1) - wolf->pos_x)
		{
			wolf->side = 0;
			wall_y = (int)wall_y + wolf->inc_y;
			wall_x = (wall_y - wolf->y_int) / wolf->slope;
			if (wall_x > wolf->map_choice)
				wall_x = wolf->map_choice;
			else if (wall_x < 0)
				wall_x = 0;
		}
		else
		{
			wolf->side = 1;
			wall_x = (int)wall_x + wolf->inc_x;
			wall_y = (wolf->slope * wall_x) + wolf->y_int;
			if (wall_y > 14.0)
				wall_y = 14.0;
			else if (wall_y < 0)
				wall_y = 0;
		}
		if (wolf->map[(int)wall_y] && wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
			break;
	}
	wolf->distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
	printf("%f\n", wolf->distance);
}

void					aim_ray(t_env *env, t_wolf *wolf, int pixel)
{
	double	rotate_view;

	rotate_view = ((2 * pixel) / (double)WIN_LEN) - 1;
	printf("rotate_view%f\n", rotate_view);
	wolf->ray_vector_x = wolf->vector_x + wolf->fov_x * rotate_view;
	wolf->ray_vector_y = wolf->vector_y + wolf->fov_y * rotate_view;
	wolf->inc_x = (wolf->ray_vector_x < 0) ? -1 : 1;
	wolf->inc_y = (wolf->ray_vector_y < 0) ? -1 : 1;
	if ((wolf->pos_x + wolf->ray_vector_x) - wolf->pos_x == 0)
		wolf->slope = ((wolf->pos_y + wolf->ray_vector_y) - wolf->pos_y) / 0.0001;
	else
		wolf->slope = ((wolf->pos_y + wolf->ray_vector_y) - wolf->pos_y) / ((wolf->pos_x + wolf->ray_vector_x) - wolf->pos_x);
	wolf->y_int = -(wolf->slope * wolf->pos_x) + wolf->pos_y;
	printf("slope%f\n", wolf->slope);
	printf("xrayvec%f\n", wolf->ray_vector_x);
	printf("yrayvec%f\n", wolf->ray_vector_y);
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
			if (!(wolf->map[y] & 0b1 << x++))
				break;
		if (!(wolf->map[y++] & 0b1 << x))
			break;
	}
	wolf->pos_x = x;
	wolf->pos_y = y;
	wolf->vector_x = -1;
	wolf->vector_y = 0;
	wolf->fov_x = 0;
	wolf->fov_y = 0.66;
}

void					raycaster(t_env *env, t_wolf *wolf)
{
	int 	pixel;

	pixel = 0;
	if (env->reinit == false)
		ray_init(env, wolf);
	while (pixel < (WIN_LEN - 1))
	{
		aim_ray(env, wolf, pixel);
		shoot_ray(env, wolf);
		draw_wall(env, wolf, pixel);
		pixel++;
	}
}
