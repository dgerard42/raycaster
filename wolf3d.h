/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:29:46 by dgerard           #+#    #+#             */
/*   Updated: 2017/10/06 16:05:27 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "minilibx/mlx.h"
# include <stdbool.h>
# include <math.h>

# define WIN_HI		800
# define WIN_LEN	1201
# define SCALE		64  //maybe implement an int scale instead of doubles later
# define WOLF		(env->wolf_mem)
# define SPEED		0.1

# define KEY_ESC	53
# define KEY_W		13
# define KEY_S		1
# define KEY_A		0
# define KEY_D		2
# define KEY_M      46

typedef	struct		s_wolf
{
	int				map_choice;
	unsigned long	*map;
	double			pos_x;
	double			pos_y;
	double			vector_x;
	double			vector_y;
	double			fov_x;
	double			fov_y;
	double			ray_vector_x;
	double			ray_vector_y;
	int				inc_x;
	int				inc_y;
	double			slope;
	double			y_int;
	double			distance;
	int				side;
	bool			minimap;
}					t_wolf;

typedef	struct		s_env
{
	void			*mlx;
	void			*window;
	void			*image;
	int				*pixels;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	bool			reinit;
	t_wolf			*wolf_mem;
}					t_env;

void				raycaster(t_env *env, t_wolf *wolf);
int					key_controls(int keycode, t_env *env);
void				reinit(t_env *env, t_wolf *wolf);
void				welcome_user(void);
void				map_0(t_wolf *wolf);
void				map_1(t_wolf *wolf);
void				map_2(t_wolf *wolf);

#endif
