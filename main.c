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
	else
		env->window = mlx_new_window(env->mlx, WIN_LEN, WIN_HI, "escape the maze");
	env->image = mlx_new_image(env->mlx, WIN_LEN, WIN_HI);
	env->pixels = (int *)mlx_get_data_addr(env->image, &env->bits_per_pixel,
		&env->size_line, &env->endian);
	raycaster(env, wolf);
	mlx_put_image_to_window(env->mlx, env->window, env->image, 0, 0);
}

void		map_0(t_wolf *wolf)
{
	//17
	wolf->map = (unsigned long *)malloc(sizeof(unsigned long) * 15);
	wolf->map[0] = 0b11111111111111111;
	wolf->map[1] = 0b10001000100010001;
	wolf->map[2] = 0b10000000000000001;
	wolf->map[3] = 0b10000000000000001;
	wolf->map[4] = 0b10000000100000001;
	wolf->map[5] = 0b11000001110000011;
	wolf->map[6] = 0b10000011111000001;
	wolf->map[7] = 0b10000001110000001;
	wolf->map[8] = 0b10000011111000001;
	wolf->map[9] = 0b11000001110000011;
	wolf->map[10] = 0b10000000100000001;
	wolf->map[11] = 0b10000000000000001;
	wolf->map[12] = 0b10000000000000001;
	wolf->map[13] = 0b10001000100010001;
	wolf->map[14] = 0b11111111111111111;
}

void		map_1(t_wolf *wolf)
{
	//18
	wolf->map = (unsigned long *)malloc(sizeof(unsigned long) * 15);
	wolf->map[0] = 0b111111111111111111;
	wolf->map[1] = 0b101100000010000001;
	wolf->map[2] = 0b100001011000101101;
	wolf->map[3] = 0b110111001101100101;
	wolf->map[4] = 0b100001100100101111;
	wolf->map[5] = 0b101101101110100001;
	wolf->map[6] = 0b100101100010111101;
	wolf->map[7] = 0b110100111010001101;
	wolf->map[8] = 0b110110100011100001;
	wolf->map[9] = 0b110010001110001011;
	wolf->map[10] = 0b111010100010111011;
	wolf->map[11] = 0b100010111011100001;
	wolf->map[12] = 0b101110001000111111;
	wolf->map[13] = 0b100011011110000001;
	wolf->map[14] = 0b111111111111111111;
}

void		map_2(t_wolf *wolf)
{
	//30
	wolf->map[0] = 0b11111111111111111111111111111111;
	wolf->map[1] = 0b10000110000010000100000010000111;
	wolf->map[2] = 0b10110000111011010110111010110111;
	wolf->map[3] = 0b10011011101110000000101010110001;
	wolf->map[4] = 0b11011011001111110110001000010101;
	wolf->map[5] = 0b11010001100001000011101111010001;
	wolf->map[6] = 0b10010101001011011000100100011011;
	wolf->map[7] = 0b10111101101000001110110101000011;
	wolf->map[8] = 0b10101000000011011100100101101111;
	wolf->map[9] = 0b10101110110110000101110111000001;
	wolf->map[10] = 0b10001000011100110101000001110111;
	wolf->map[11] = 0b10100011000101100001101100000011;
	wolf->map[12] = 0b10111010011101101100101110111001;
	wolf->map[13] = 0b11100011010000001110001000110001;
	wolf->map[14] = 0b11111111111111111111111111111111;
}

int			main(int argc, char **argv)
{
	t_env	env;
	t_wolf	wolf;

	if (argc != 2)
		return(0);
	env.mlx = mlx_init();
	wolf.map_choice = ft_atoi(argv[1]);
	//implement parameter managment and a menu later, this is v sloppy open to segfaults
	wolf.map = (unsigned long *)malloc(sizeof(unsigned long) * 15);
	if (wolf.map_choice == 16)
		map_0(&wolf);
	else if (wolf.map_choice == 17)
		map_1(&wolf);
	else if (wolf.map_choice == 29)
		map_2(&wolf);
	env.reinit = false;
	reinit(&env, &wolf);
	// mlx_hook(env.window, 2, 0, key_controls, (void *)&env);
	// mlx_mouse_hook(env.window, &mouse_controls, (void *)&env);
	// mlx_hook(env.window, 6, 0, another_ft, (void *)&env);
	mlx_loop(env.mlx);
	return (0);
}
