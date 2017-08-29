/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 15:15:31 by dgerard           #+#    #+#             */
/*   Updated: 2017/08/28 15:15:32 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void				shoot_ray()
{
	wolf->check_x = wolf->pos_x;
	wolf->check_y = wolf->pos_y;
	while (1)
	{
		if (((int)wolf->check_y + 1) - wolf->pos_y < ((int)wolf->check_x + 1) - wolf->pos_x)
		{
			wolf->check_y = (int)wolf->check_y + 1;
			wolf->check_x = (wolf->check_y - wolf->y_int) / wolf->slope;
			if (wolf->map[(int)wolf->check_y] && wolf->map[(int)wolf->check_y] & (0b1 << (int)wolf->check_x))
				break;
		}
		else
		{
			wolf->check_x = (int)wolf->check_x + 1;
			wolf->check_y = (wolf->slope * wolf->check_x) + wolf->y_int;
			if (wolf->map[(int)wolf->check_y] && wolf->map[(int)wolf->check_y] & (0b1 << (int)wolf->check_x))
				break;
		}
	}
}

//then use distance between check coords and pos coords to decide the size of the wall

void				raycaster()
{
	ra000
	while ()
	{

	}
	wolf->slope = (wolf->view_y - wolf->pos_y) / (wolf->view_x - wolf->pos_x);
	wolf->y_int = -(slope * wolf->pos_x) + wolf->pos_y;
}
