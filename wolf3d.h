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
# include <stdbool.h>

typedef	struct	s_env
{
	void		*mlx;
	void		*window;
	void		*image;
	int			*pixels;
	int			*bits_per_pixel;
	int			size_line;
	int			endian;
	bool		reinit;
}				t_mlx;

typedef	struct			s_wolf
{
	int					map_choice;
	unsigned long long 	*map;
	float				pos_x;
	float				pos_y;
	float				view_x;
	float				view_y;
	float				slope;
	float				y_int;

}						t_wolf;

#endif
