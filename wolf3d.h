/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:29:46 by dgerard           #+#    #+#             */
/*   Updated: 2017/08/28 11:59:10 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <stdbool.h>
# include <math.h>
# include <stdio.h> //rm this at the end

# define WIN_HI		800
# define WIN_LEN	1200

# define KEY_ESC
# define KEY_W
# define KEY_D

typedef	struct	s_env
{
	void		*mlx;
	void		*window;
	void		*image;
	int			*pixels;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	bool		reinit;
}				t_env;

typedef	struct			s_wolf
{
	int					map_choice;
	unsigned long		*map;
	float				pos_x;
	float				pos_y;
	float				view_x;
	float				view_y;
	float				slope;
	float				y_int;
	float				distance;
}						t_wolf;

void				raycaster(t_env *env, t_wolf *wolf);
//remember to rm this prototype VV
int					ft_printf(const char *format, ...);
int					key_controls(int keycode, t_env *env);

#endif
