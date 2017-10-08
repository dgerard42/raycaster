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

void			minimap(t_wolf *wolf)
{
	int x;
	int y = 0;

	while (y < 15)
	{
		x = 0;
		while (x <= wolf->map_choice)
		{
			if ((int)wolf->pos_x == x && (int)wolf->pos_y == y)
				ft_putstr(".X");
			else if ((int)(wolf->pos_x + wolf->ray_vector_x) == x && (int)(wolf->pos_y + wolf->ray_vector_y) == y)
				ft_putstr(".x");
			else if (wolf->map[y] && wolf->map[y] & (0b1 << x))
				ft_putstr("##");
			else
				ft_putstr("..");
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	ft_printf("player position = (%d, %d)\n", (int)wolf->pos_x, (int)wolf->pos_y);
	ft_printf("view vector = (%d, %d)\n", (int)wolf->pos_x + (int)wolf->ray_vector_x, (int)wolf->pos_y + (int)wolf->ray_vector_y);
}

void			reinit(t_env *env, t_wolf *wolf)
{
	int len;
	int hi;

	if (env->reinit == true)
		mlx_destroy_image(env->mlx, env->image);
	else
	{
		system("afplay ./support_files/alien_pollen.mp3&");
		env->window = mlx_new_window(env->mlx, WIN_LEN, WIN_HI, "welcome to hell");
	}
	env->image = mlx_xpm_file_to_image(env->mlx, "./support_files/stars_1201_800.xpm", &len, &hi);
	env->pixels = (int *)mlx_get_data_addr(env->image, &env->bits_per_pixel, &env->size_line, &env->endian);
	raycaster(env, wolf);
	mlx_put_image_to_window(env->mlx, env->window, env->image, 0, 0);
	minimap(wolf);
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
	wolf->map_choice = 17;
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
	wolf->map_choice = 31;
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
	// fake_rand_setup(&wolf);
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
