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
	float	check_x;
	float	check_y;
	//float	current_x;
	//float	current_y;

	check_x = wolf->pos_x;
	check_y = wolf->pos_y;
	while (obstacle not hit)
	{
		if (((int)check_y + 1) - wolf->pos_y < ((int)check_x + 1) - wolf->pos_x)
		{
			
		}
		else
		{

		}
	}
}

void				raycaster()
{

	wolf->slope = (wolf->view_y - wolf->pos_y) / (wolf->view_x - wolf->pos_x);
	wolf->y_int =
}
