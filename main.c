/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 12:20:54 by dgerard           #+#    #+#             */
/*   Updated: 2017/09/04 17:04:28 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			reinit(t_env *env, t_wolf *wolf)
{
	if (env->reinit == true)
		mlx_destroy_image(env->mlx, env->image);
	env->image = mlx_new_image(env->mlx, WIN_HI, WIN_LEN);
	env->pixels = (int *)mlx_get_data_addr(env->image, &env->bits_per_pixel,
		&env->size_line, &env->endian);
	raycaster(env, wolf);
	mlx_put_image_to_window(env->mlx, env->window, env->image, 0, 0);
}

int			main(void)
{
	t_env env;
	t_wolf wolf;

	env.mlx = mlx_init();
	wolf.map = {0b11111111111111111, 0b10001000100010001, 0b10000000000000001,
				0b10000000000000001, 0b10000000100000001, 0b11000001110000011,
				0b10000011111000001, 0b10000001110000001, 0b10000011111000001,
				0b11000001110000011, 0b10000000100000001, 0b10000000000000001,
				0b10000000000000001, 0b10001000100010001, 0b11111111111111111};
	env.reinit = false;
	reinit(&env, &wolf);
	// mlx_hook(env.window, 2, 0, key_controls, (void *)&env);
	// mlx_mouse_hook(env.window, &mouse_controls, (void *)&env);
	// mlx_hook(env.window, 6, 0, another_ft, (void *)&env);
	mlx_loop(env.mlx);
	return (0);
}
