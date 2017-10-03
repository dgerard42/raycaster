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

int						fade_color(int color)
{
	int red;
	int	green;
	int	blue;
	int return_color;

	return_color = 0;
	// printf("original%x\n", color);
	blue = color % 0x100;
	green = (color % 0x10000) / 0x100;
	red = (color % 0x1000000) / 0x10000;
	// printf("r%d, g%d, b%d\n", red, green, blue);
	red = (red - 1 > 0) ? red - 1 : red;
	blue = (blue - 1 > 0) ? blue - 1 : blue;
	green = (green - 1 > 0) ? green - 1 : green;
	// printf("r%d, g%d, b%d\n", red, green, blue);
	return_color += red * 0x10000;
	return_color += green * 0x100;
	return_color += blue;
	// printf("darker%x\n", return_color);
	return(return_color);
}

int						choose_color(t_wolf *wolf)
{
	int return_color;

	return_color = 0x00FF00;
	if (wolf->side == 0)
	{
		if (wolf->inc_x == 1)
			return_color = 0xbff0ff;
		else if (wolf->inc_x == -1)
			return_color = 0xbadaff;
	}
	else if (wolf->side == 1)
	{
		if (wolf->inc_y == 1)
			return_color = 0xaf9dff;
		else if (wolf->inc_y == -1)
			return_color = 0xb080ee;
	}
	while (return_color > 0x000000 && wolf->distance > 0.0)
	{
		return_color = fade_color(return_color);
		wolf->distance -= 0.1;
	}
	return (return_color);
}

void					draw_wall(t_env *env, t_wolf *wolf, int pixel)
{
	int y;
	int	sky;
	int	wall_hi;
	int	color;

	y = 0;
	// if (0x0000FF - (wolf->distance * 12) > 0x000000)
	// 	color = 0x0000FF - (wolf->distance * 12);
	// else
	// 	color = 0x000000;
	// if (wolf->side == 1 && color - 32 > 0x000000)
	// 	color -= 32;
	wall_hi = (wolf->distance == 0) ? WIN_HI - 6 : WIN_HI / wolf->distance;
	sky = (WIN_HI - wall_hi) / 2;
	color = choose_color(wolf);
	while (y < sky)
		env->pixels[pixel + (y++ * WIN_LEN)] = 0x000000;
	while (wall_hi-- > 0)
		env->pixels[pixel + (y++ * WIN_LEN)] = color;
	while (y < (WIN_HI - 1))
		env->pixels[pixel + (y++ * WIN_LEN)] = 0x9D54D0;
}

void				shoot_yray(t_wolf *wolf)
{
	double	wall_y;
	double	wall_x;
	double	distance;

	wall_y = wolf->pos_y;
	wall_x = wolf->pos_x;
	while (1 && wolf->map[(int)wall_y])
	{
		if (wolf->inc_y == 1)
			if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break;
		if (wolf->inc_y == -1)
			if (wolf->map[(int)wall_y - 1] & (0b1 << ((int)wall_x + 0)))
				break;
		wall_y = (int)wall_y + wolf->inc_y;
		wall_x = (wall_y - wolf->y_int) / wolf->slope;
		if (wall_x > wolf->map_choice)
			wall_x = wolf->map_choice;
		else if (wall_x < 0)
			wall_x = 0;
	}
	distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
	if (distance < wolf->distance)
	{
		wolf->distance = distance;
		wolf->side = 1;
	}
}

void				shoot_xray(t_wolf *wolf)
{
	double 	wall_x;
	double	wall_y;

	wall_x = wolf->pos_x;
	wall_y = wolf->pos_y;
	while (1 && wolf->map[(int)wall_y])
	{
		if (wolf->inc_x == 1)
			if (wolf->map[(int)wall_y + 0] & (0b1 << ((int)wall_x + 0)))
				break;
		if (wolf->inc_x == -1)
			if (wolf->map[(int)wall_y + 0] & (0b1 << ((int)wall_x - 1)))
				break;
		wall_x = (int)wall_x + wolf->inc_x; //typecasting as an int here allows an even increment to the next whole # from a possible decimaled starting point
		wall_y = (wolf->slope * wall_x) + wolf->y_int;
		if (wall_y > 14.0)
			wall_y = 14.0;
		else if (wall_y < 0)
			wall_y = 0;
	}
	wolf->distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
	wolf->side = 0;
}

void					aim_ray(t_wolf *wolf, int pixel)
{
	double	rotate_view;

	rotate_view = ((2 * pixel) / (double)WIN_LEN) - 1;
	wolf->ray_vector_x = wolf->vector_x + wolf->fov_x * rotate_view;
	wolf->ray_vector_y = wolf->vector_y + wolf->fov_y * rotate_view;
	wolf->inc_x = (wolf->ray_vector_x < 0) ? -1 : 1;
	wolf->inc_y = (wolf->ray_vector_y < 0) ? -1 : 1;
	if ((wolf->pos_x + wolf->ray_vector_x) - wolf->pos_x == 0)
		wolf->slope = ((wolf->pos_y + wolf->ray_vector_y) - wolf->pos_y) / 0.0001;
	else
		wolf->slope = ((wolf->pos_y + wolf->ray_vector_y) - wolf->pos_y) / ((wolf->pos_x + wolf->ray_vector_x) - wolf->pos_x);
	wolf->y_int = -(wolf->slope * wolf->pos_x) + wolf->pos_y;
}

void					ray_init(t_wolf *wolf)
{
	int x;
	int y;

	y = 0;
	while (y < 15)
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
		ray_init(wolf);
	while (pixel < (WIN_LEN - 1))
	{
		aim_ray(wolf, pixel);
		// shoot_ray(wolf);
		shoot_xray(wolf);
		shoot_yray(wolf);
		draw_wall(env, wolf, pixel);
		pixel++;
	}
	printf("side = %d\n", wolf->side);
	printf("inc_x%d\n", wolf->inc_x);
	printf("inc_y%d\n", wolf->inc_y);
}
