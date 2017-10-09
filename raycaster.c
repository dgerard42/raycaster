/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 15:05:31 by dgerard           #+#    #+#             */
/*   Updated: 2017/10/06 17:03:15 by dgerard          ###   ########.fr       */
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
	blue = color % 0x100;
	green = (color % 0x10000) / 0x100;
	red = (color % 0x1000000) / 0x10000;
	red = (red - 1 > 0) ? red - 1 : red;
	blue = (blue - 1 > 0) ? blue - 1 : blue;
	green = (green - 1 > 0) ? green - 1 : green;
	return_color += red * 0x10000;
	return_color += green * 0x100;
	return_color += blue;
	return(return_color);
}

int						choose_color(t_wolf *wolf)
{
	int 	return_color;
	double	dist_tmp;

	return_color = 0x00FF00;
	dist_tmp = wolf->distance;
	if (wolf->side == 0)
		return_color = (wolf->inc_x == 1) ? 0xa2bbff : 0xb080ee;
	else if (wolf->side == 1)
		return_color = (wolf->inc_y == 1) ? 0xaf9dff : 0xbff0ff;
	while (return_color > 0x000000 && dist_tmp > 0.0)
	{
		return_color = fade_color(return_color);
		dist_tmp -= 0.08;
	}
	return (return_color);
}

int						fake_rand(unsigned int range_lo, unsigned int range_hi, unsigned int seed)
{
	int				seed_2;
	unsigned int	bit;
	unsigned int 	revuelto;

	bit = 0;
	revuelto = 0;
	seed_2 = 293482;
	if (range_lo == range_hi)
		return (range_lo);
	revuelto = revuelto^seed_2;
	bit = ((seed >> 0) ^ (seed >> 2) ^ (seed >> 3) ^ (seed >> 5)) & 1;
	seed = ((bit << 15) | (seed >> 1) | revuelto) % range_hi;
	while (seed < range_lo)
	 	seed = seed + range_hi - range_lo;
	return ((int)seed);
}

void					draw_wall(t_env *env, t_wolf *wolf, int pixel)
{
	int y;
	int	sky;
	int	wall_hi;
	int	color;
	int seed;

	y = 0;
	seed = 38947;
	wall_hi = (wolf->distance == 0) ? WIN_HI - 6 : WIN_HI / wolf->distance;
	while (wall_hi > (WIN_HI - 1))
		wall_hi--;
	sky = (WIN_HI - wall_hi) / 2;
	color = choose_color(wolf);
	while (y < sky)
		y++;
	while (wall_hi-- > 0)
		env->pixels[pixel + (y++ * WIN_LEN)] = color;
	while (y < (WIN_HI - 1))
	{
		if (pixel % fake_rand(10, 400, seed++) || y % fake_rand(10, 400, seed++))
			env->pixels[pixel + (y++ * WIN_LEN)] = 0x000000;
		else
			env->pixels[pixel + (y++ * WIN_LEN)] = 0xFFFFFF;
	}
}

// void				shoot_yray(t_wolf *wolf)
// {
// 	double	wall_y;
// 	double	wall_x;
// 	double	distance;
//
// 	wall_y = wolf->pos_y;
// 	wall_x = wolf->pos_x;
// 	while (1 && wolf->map[(int)wall_y])
// 	{
// 		if (wolf->inc_y == 1)
// 			if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
// 				break;
// 		if (wolf->inc_y == -1)
// 			if (wolf->map[(int)wall_y - 1] & (0b1 << (int)wall_x))
// 				break;
// 		wall_y = (int)wall_y + wolf->inc_y;
// 		wall_x = (wall_y - wolf->y_int) / wolf->slope;
// 		if (wall_x > wolf->map_choice)
// 			wall_x = wolf->map_choice;
// 		else if (wall_x < 0)
// 			wall_x = 0;
// 	}
// 	distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
// 	if (distance < wolf->distance)
// 	{
// 		wolf->distance = distance;
// 		wolf->side = 1;
// 	}
// }
//
// void				shoot_xray(t_wolf *wolf)
// {
// 	double 	wall_x;
// 	double	wall_y;
//
// 	wall_y = wolf->pos_y;
// 	wall_x = wolf->pos_x;
// 	while (1 && wolf->map[(int)wall_y])
// 	{
// 		if (wolf->inc_x == 1)
// 			if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
// 				break;
// 		if (wolf->inc_x == -1)
// 			if (wolf->map[(int)wall_y] & (0b1 << ((int)wall_x - 1)))
// 				break;
// 		wall_x = (int)wall_x + wolf->inc_x;
// 		wall_y = (wolf->slope * wall_x) + wolf->y_int;
// 		if (wall_y > 14.0)
// 			wall_y = 14.0;
// 		else if (wall_y < 0)
// 			wall_y = 0;
// 	}
// 	wolf->distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) + powf(wall_y - wolf->pos_y, 2.0));
// 	wolf->side = 0;
// }

void					shoot_ray(t_wolf *wolf)
{
	double	wall_x;
	double	wall_y;

	wall_x = wolf->pos_x;
	wall_y = wolf->pos_y;
	while (1 && wolf->map[(int)wall_y])
	{
		if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
			break;
		if (wolf->ray_vector_x < 1)
			wall_x = (wolf->ray_vector_x)
		else
			wall_x =
		if (wolf->ray_vector_y < 1)
			wall_y =
		else
			wall_y =
	}
}

void					aim_ray(t_wolf *wolf, int pixel)
{
	double	rotate_view;

	rotate_view = ((2 * pixel) / (double)WIN_LEN) - 1;
	wolf->ray_vector_x = wolf->vector_x + wolf->fov_x * rotate_view;
	wolf->ray_vector_y = wolf->vector_y + wolf->fov_y * rotate_view;
	wolf->inc_x = (wolf->ray_vector_x < 0) ? -1 : 1;
	wolf->inc_y = (wolf->ray_vector_y < 0) ? -1 : 1;
	// if ((wolf->pos_x + wolf->ray_vector_x) - wolf->pos_x == 0)
	// 	wolf->slope = ((wolf->pos_y + wolf->ray_vector_y) - wolf->pos_y) / 0.0001;
	// else
	// 	wolf->slope = ((wolf->pos_y + wolf->ray_vector_y) - wolf->pos_y) / ((wolf->pos_x + wolf->ray_vector_x) - wolf->pos_x);
	// wolf->y_int = -(wolf->slope * wolf->pos_x) + wolf->pos_y;
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
		shoot_ray(wolf);
		// shoot_xray(wolf);
		// shoot_yray(wolf);
		draw_wall(env, wolf, pixel);
		pixel++;
	}
}
