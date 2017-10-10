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

void			welcome_user(void)
{
	ft_putstr("----------welcome user (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧----------\n");
	ft_putstr("ESC == exit program\nW == move forwards\n");
	ft_putstr("S == move backwards\nA == rotate left\nD == rotate right\n");
	ft_putstr("M == toggle minimap\n");
	ft_putstr("---------------------------------------------\n");
}

void			minimap(t_wolf *wolf)
{
	int x;
	int y;

	y = 0;
	while (y < 15)
	{
		x = 0;
		while (x <= wolf->map_choice)
		{
			if ((int)wolf->pos_x == x && (int)wolf->pos_y == y)
				ft_putstr(".X");
			else if ((int)(wolf->pos_x + wolf->ray_vector_x) == x &&
				(int)(wolf->pos_y + wolf->ray_vector_y) == y)
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
	ft_printf("player position = (%d, %d)\n", (int)wolf->pos_x,
		(int)wolf->pos_y);
	ft_printf("view vector = (%d, %d)\n", (int)wolf->pos_x +
		(int)wolf->ray_vector_x, (int)wolf->pos_y + (int)wolf->ray_vector_y);
}

void			reinit(t_env *env, t_wolf *wolf)
{
	int len;
	int hi;

	if (env->reinit == true)
		mlx_destroy_image(env->mlx, env->image);
	else
		env->window = mlx_new_window(env->mlx, WIN_LEN, WIN_HI, "welcome to hell");
	env->image = mlx_xpm_file_to_image(env->mlx, "./support_files/stars_1201_800.xpm", &len, &hi);
	env->pixels = (int *)mlx_get_data_addr(env->image, &env->bits_per_pixel, &env->size_line, &env->endian);
	raycaster(env, wolf);
	mlx_put_image_to_window(env->mlx, env->window, env->image, 0, 0);
	if (wolf->minimap == true)
		minimap(wolf);
}



void			handle_parameters(t_wolf *wolf, int argc, char **parameters)
{
	wolf->map_choice = 42;
	if (parameters[1])
	{
		if (ft_strequ(parameters[1], "blox"))
			map_0(wolf);
		else if (ft_strequ(parameters[1], "maze"))
			map_1(wolf);
		else if (ft_strequ(parameters[1], "box"))
			map_2(wolf);
	}
	// printf("%d\n", argc);
	if (argc != 2 || wolf->map_choice == 42)
	{
		ft_putstr("Error. Invalid input.\n");
		ft_putstr("Usage:  [blox] = some pillars n blox\n\t");
		ft_putstr("[maze] = a stupid maze\n\t[box] = big ass box\n");
		exit(0);
	}
}

int				main(int argc, char **argv)
{
	t_env	env;
	t_wolf	wolf;

	if (argc != 2)
		return(0);
	env.mlx = mlx_init();
	handle_parameters(&wolf, argc, argv);
	env.wolf_mem = &wolf;
	env.reinit = false;
	wolf.minimap = false;
	// system("afplay ./support_files/alien_pollen.mp3&");
	reinit(&env, &wolf);
	welcome_user();
	mlx_hook(env.window, 2, 0, key_controls, (void *)&env);
	mlx_loop(env.mlx);
	return (0);
}
