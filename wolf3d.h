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
# include <unistd.h> //again, rm at end
# include <stdio.h> //rm this at the end

# define WIN_HI		800
# define WIN_LEN	1200

# define KEY_ESC	53
# define KEY_W		13
# define KEY_S		1
# define KEY_A		0
# define KEY_D		2
# define KEY_O		31
# define KEY_P		35

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
	void		*wolf_mem;
}				t_env;

typedef	struct			s_wolf
{
	int					map_choice;
	unsigned long		*map;
	float				pos_x;
	float				pos_y;
	float				view_x;
	float				view_y;
	// float				slope_static;
	float				slope;
	float				rise;
	float				run;
	// float				inv_slope;
	float				y_int;
	float				distance;
	int					inc_x;
	int					inc_y;
	// float				radians;
	int					wall_color;
}						t_wolf;

void				raycaster(t_env *env, t_wolf *wolf);
int					key_controls(int keycode, t_env *env);
void				reinit(t_env *env, t_wolf *wolf);
//remember to rm this prototype VV
int					ft_printf(const char *format, ...);

#endif
