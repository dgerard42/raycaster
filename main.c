/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 12:20:54 by dgerard           #+#    #+#             */
/*   Updated: 2017/10/06 16:05:03 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			minimap_debugger(t_wolf *wolf)
{
	int x;
	int y = 0;

	while (y < 15)
	{
		x = 0;
		while (x <= wolf->map_choice)
		{
			if ((int)wolf->pos_x == x && (int)wolf->pos_y == y)
				write(1, "X", 1);
			else if ((int)(wolf->pos_x + wolf->ray_vector_x) == x && (int)(wolf->pos_y + wolf->ray_vector_y) == y)
				write(1, "x", 1);
			else if (wolf->map[y] && wolf->map[y] & (0b1 << x))
				write(1, "#", 1);
			else
				write(1, ".", 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
	printf("posy%f ", wolf->pos_y);
	printf("posx%f\n", wolf->pos_x);
	printf("view_y%f ", wolf->pos_y + wolf->ray_vector_y);
	printf("view_x%f\n", wolf->pos_x + wolf->ray_vector_x);
}

void			reinit(t_env *env, t_wolf *wolf)
{
	int len;
	int hi;

	if (env->reinit == true)
		mlx_destroy_image(env->mlx, env->image);
	else
		env->window = mlx_new_window(env->mlx, WIN_LEN, WIN_HI, "welcome to hell");
	// env->image = mlx_new_image(env->mlx, WIN_LEN, WIN_HI);
	env->image = mlx_xpm_file_to_image(env->mlx, "/nfs/2017/d/dgerard/Desktop/stars_1201_800.xpm", &len, &hi);
	printf("%d, %d\n", len, hi);
	env->pixels = (int *)mlx_get_data_addr(env->image, &env->bits_per_pixel, &env->size_line, &env->endian);
	printf("here0\n");
	raycaster(env, wolf);
	printf("here1\n");
	mlx_put_image_to_window(env->mlx, env->window, env->image, 0, 0);
	minimap_debugger(wolf);
	printf("here2\n");
}

void		map_0(t_wolf *wolf)
{
	// printf("map 0!!\n");
	wolf->map_choice = 16;
	wolf->map[0x0] = 0b11111111111111111;
	wolf->map[0x1] = 0b10001000100010001;
	wolf->map[0x2] = 0b10000000000000001;
	wolf->map[0x3] = 0b10000000000000001;
	wolf->map[0x4] = 0b10000000100000001;
	wolf->map[0x5] = 0b11000001110000011;
	wolf->map[0x6] = 0b10000011111000001;
	wolf->map[0x7] = 0b10000001110000001;
	wolf->map[0x8] = 0b10000011111000001;
	wolf->map[0x9] = 0b11000001110000011;
	wolf->map[0xa] = 0b10000000100000001;
	wolf->map[0xb] = 0b10000000000000001;
	wolf->map[0xc] = 0b10000000000000001;
	wolf->map[0xd] = 0b10001000100010001;
	wolf->map[0xe] = 0b11111111111111111;
	wolf->map[0xf] = 0;
}

void		map_1(t_wolf *wolf)
{
	// printf("map 1!!\n");
	wolf->map_choice = 17;
//	wolf->map = (unsigned long *)malloc(sizeof(unsigned long) * 15);
	// wolf->map[0x0] = 0b111111111111111111;
	// wolf->map[0x1] = 0b101100000010000001;
	// wolf->map[0x2] = 0b100001011000101101;
	// wolf->map[0x3] = 0b110111001101100101;
	// wolf->map[0x4] = 0b100001100100101111;
	// wolf->map[0x5] = 0b101101101110100001;
	// wolf->map[0x6] = 0b100101100010111101;
	// wolf->map[0x7] = 0b110100111010001101;
	// wolf->map[0x8] = 0b110110100011100001;
	// wolf->map[0x9] = 0b110010001110001011;
	// wolf->map[0xa] = 0b111010100010111011;
	// wolf->map[0xb] = 0b100010111011100001;
	// wolf->map[0xc] = 0b101110001000111111;
	// wolf->map[0xd] = 0b100011011110000001;
	// wolf->map[0xe] = 0b111111111111111111;
	// wolf->map[0xf] = 0;
	wolf->map[0x0] = 0b111111111111111111;
	wolf->map[0x1] = 0b100010000000000001;
	wolf->map[0x2] = 0b100010101010000001;
	wolf->map[0x3] = 0b100010000000011001;
	wolf->map[0x4] = 0b100010001110011001;
	wolf->map[0x5] = 0b100011001010011001;
	wolf->map[0x6] = 0b100000001000011001;
	wolf->map[0x7] = 0b100000001000011001;
	wolf->map[0x8] = 0b111100111111111001;
	wolf->map[0x9] = 0b100100100000011001;
	wolf->map[0xa] = 0b100100100000011001;
	wolf->map[0xb] = 0b100111100010000001;
	wolf->map[0xc] = 0b100000000010000001;
	wolf->map[0xd] = 0b100000000010000001;
	wolf->map[0xe] = 0b111111111111111111;
	wolf->map[0xf] = 0;
}

void		map_2(t_wolf *wolf)
{
	// printf("map 2!!\n");
	wolf->map_choice = 31;
	// wolf->map[0] = 0b11111111111111111111111111111111;
	// wolf->map[1] = 0b10000110000010000100000010000111;
	// wolf->map[2] = 0b10110000111011010110111010110111;
	// wolf->map[3] = 0b10011011101110000000101010110001;
	// wolf->map[4] = 0b11011011001111110110001000010101;
	// wolf->map[5] = 0b11010001100001000011101111010001;
	// wolf->map[6] = 0b10010101001011011000100100011011;
	// wolf->map[7] = 0b10111101101000001110110101000011;
	// wolf->map[8] = 0b10101000000011011100100101101111;
	// wolf->map[9] = 0b10101110110110000101110111000001;
	// wolf->map[10] = 0b10001000011100110101000001110111;
	// wolf->map[11] = 0b10100011000101100001101100000011;
	// wolf->map[12] = 0b10111010011101101100101110111001;
	// wolf->map[13] = 0b11100011010000001110001000110001;
	// wolf->map[14] = 0b11111111111111111111111111111111;
	wolf->map[0x0] = 0b11111111111111111111111111111111;
	wolf->map[0x1] = 0b10000000000000000000000000000001;
	wolf->map[0x2] = 0b10000000000000000000000000000001;
	wolf->map[0x3] = 0b10000000000000000000000000000001;
	wolf->map[0x4] = 0b10000000000000000000000000000001;
	wolf->map[0x5] = 0b10000000000000000000000000000001;
	wolf->map[0x6] = 0b10000000000000000000000000000001;
	wolf->map[0x7] = 0b10000000000000000000000000000001;
	wolf->map[0x8] = 0b10000000000000000000000000000001;
	wolf->map[0x9] = 0b10000000000000000000000000000001;
	wolf->map[0xa] = 0b10000000000000000000000000000001;
	wolf->map[0xb] = 0b10000000000000000000000000000001;
	wolf->map[0xc] = 0b10000000000000000000000000000001;
	wolf->map[0xd] = 0b10000000000000000000000000000001;
	wolf->map[0xe] = 0b11111111111111111111111111111111;
	wolf->map[0xf] = 0;
}

int			main(int argc, char **argv)
{
	t_env	env;
	t_wolf	wolf;

	if (argc != 2)
		return(0);
	env.mlx = mlx_init();
	wolf.map_choice = ft_atoi(argv[1]);
	env.wolf_mem = &wolf;
	//implement parameter managment and a menu later, this is v sloppy open to segfaults
	wolf.map = (unsigned long *)malloc(sizeof(unsigned long) * 16);
	if (wolf.map_choice == 0)
		map_0(&wolf);
	else if (wolf.map_choice == 1)
		map_1(&wolf);
	else if (wolf.map_choice == 2)
		map_2(&wolf);
	env.reinit = false;
	reinit(&env, &wolf);
	mlx_hook(env.window, 2, 0, key_controls, (void *)&env);
	// mlx_mouse_hook(env.window, &mouse_controls, (void *)&env);
	// mlx_hook(env.window, 6, 0, another_ft, (void *)&env);
	//printf("wolf->view_x = %f\n", wolf.view_x);
	mlx_loop(env.mlx);
	return (0);
}
