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

void				shoot_yray(t_wolf *wolf)
{
	double	wall_y;
	double	wall_x;
	double	distance;

	wall_y = (wolf->inc_y == -1) ? wolf->pos_y + 1 : wolf->pos_y;
	wall_x = wolf->pos_x;
	while (1 && wolf->map[(int)wall_y])
	{
		if (wolf->inc_y == 1)
			if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break ;
		if (wolf->inc_y == -1)
			if (wolf->map[(int)wall_y - 1] & (0b1 << (int)wall_x))
				break ;
		wall_y = (int)wall_y + wolf->inc_y;
		wall_x = (wall_y - wolf->y_int) / wolf->slope;
		if (wall_x > wolf->map_choice)
			wall_x = wolf->map_choice;
		else if (wall_x < 0)
			wall_x = 0;
	}
	distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) +
		powf(wall_y - wolf->pos_y, 2.0));
	wolf->side = (distance < wolf->distance) ? 1 : 0;
	wolf->distance = (distance < wolf->distance) ? distance : wolf->distance;
}

void				shoot_xray(t_wolf *wolf)
{
	double	wall_x;
	double	wall_y;

	wall_y = wolf->pos_y;
	wall_x = (wolf->inc_x == -1) ? wolf->pos_x + 1 : wolf->pos_x;
	while (1 && wolf->map[(int)wall_y])
	{
		if (wolf->inc_x == 1)
			if (wolf->map[(int)wall_y] & (0b1 << (int)wall_x))
				break ;
		if (wolf->inc_x == -1)
			if (wolf->map[(int)wall_y] & (0b1 << ((int)wall_x - 1)))
				break ;
		wall_x = (int)wall_x + wolf->inc_x;
		wall_y = (wolf->slope * wall_x) + wolf->y_int;
		if (wall_y > 14.0)
			wall_y = 14.0;
		else if (wall_y < 0)
			wall_y = 0;
	}
	wolf->distance = sqrt(powf(wall_x - wolf->pos_x, 2.0) +
		powf(wall_y - wolf->pos_y, 2.0));
	wolf->side = 0;
}

void				aim_ray(t_wolf *wolf, int pixel)
{
	double	rotate_view;

	rotate_view = ((2 * pixel) / (double)WIN_LEN) - 1;
	wolf->ray_vec_x = wolf->vec_x + wolf->fov_x * rotate_view;
	wolf->ray_vec_y = wolf->vec_y + wolf->fov_y * rotate_view;
	wolf->inc_x = (wolf->ray_vec_x < 0) ? -1 : 1;
	wolf->inc_y = (wolf->ray_vec_y < 0) ? -1 : 1;
	if ((wolf->pos_x + wolf->ray_vec_x) - wolf->pos_x == 0)
		wolf->slope = ((wolf->pos_y + wolf->ray_vec_y) - wolf->pos_y) / 0.0001;
	else
		wolf->slope = ((wolf->pos_y + wolf->ray_vec_y) - wolf->pos_y) /
			((wolf->pos_x + wolf->ray_vec_x) - wolf->pos_x);
	wolf->y_int = -(wolf->slope * wolf->pos_x) + wolf->pos_y;
}

void				ray_init(t_wolf *wolf)
{
	int x;
	int y;

	y = 0;
	while (y < 15)
	{
		x = 0;
		while (x < wolf->map_choice)
			if (!(wolf->map[y] & 0b1 << x++))
				break ;
		if (!(wolf->map[y++] & 0b1 << x))
			break ;
	}
	wolf->pos_x = x;
	wolf->pos_y = y;
	wolf->vec_x = -1;
	wolf->vec_y = 0;
	wolf->fov_x = 0;
	wolf->fov_y = 0.66;
}

void				raycaster(t_env *env, t_wolf *wolf)
{
	int	pixel;

	pixel = 0;
	if (env->reinit == false)
		ray_init(wolf);
	while (pixel < (WIN_LEN - 1))
	{
		aim_ray(wolf, pixel);
		shoot_xray(wolf);
		shoot_yray(wolf);
		draw_wall(env, wolf, pixel);
		pixel++;
	}
}
