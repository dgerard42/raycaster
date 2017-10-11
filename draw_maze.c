/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_maze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 09:26:49 by dgerard           #+#    #+#             */
/*   Updated: 2017/10/10 09:26:55 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			fade_color(int color)
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
	return (return_color);
}

int			choose_color(t_wolf *wolf)
{
	int		return_color;
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
		dist_tmp -= 0.07;
	}
	return (return_color);
}

int			fake_rand(unsigned int lo, unsigned int hi, unsigned int seed)
{
	int				seed_2;
	unsigned int	bit;
	unsigned int	revuelto;

	bit = 0;
	revuelto = 0;
	seed_2 = 293482;
	if (lo == hi)
		return (lo);
	revuelto = revuelto ^ seed_2;
	bit = ((seed >> 0) ^ (seed >> 2) ^ (seed >> 3) ^ (seed >> 5)) & 1;
	seed = ((bit << 15) | (seed >> 1) | revuelto) % hi;
	while (seed < lo)
		seed = seed + hi - lo;
	return ((int)seed);
}

void		draw_wall(t_env *env, t_wolf *wolf, int pixel)
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
		if (pixel % fake_rand(10, 400, seed++) ||
			y % fake_rand(10, 400, seed++))
			env->pixels[pixel + (y++ * WIN_LEN)] = 0x000000;
		else
			env->pixels[pixel + (y++ * WIN_LEN)] = 0xFFFFFF;
	}
}
