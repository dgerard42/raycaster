/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 19:32:48 by dgerard           #+#    #+#             */
/*   Updated: 2017/10/08 19:32:50 by dgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		map_0(t_wolf *wolf)
{
	wolf->map = (unsigned long *)malloc(sizeof(unsigned long) * 16);
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
	wolf->map = (unsigned long *)malloc(sizeof(unsigned long) * 16);
	wolf->map_choice = 17;
	wolf->map[0x0] = 0b111111111111111111;
	wolf->map[0x1] = 0b100100000100000001;
	wolf->map[0x2] = 0b100100000100000001;
	wolf->map[0x3] = 0b100100100100111001;
	wolf->map[0x4] = 0b100100100100100001;
	wolf->map[0x5] = 0b100100100100100001;
	wolf->map[0x6] = 0b100000100100100111;
	wolf->map[0x7] = 0b100000100000100001;
	wolf->map[0x8] = 0b111111100000100001;
	wolf->map[0x9] = 0b100000100000111001;
	wolf->map[0xa] = 0b100000111111100001;
	wolf->map[0xb] = 0b100100000010000001;
	wolf->map[0xc] = 0b100000000000000001;
	wolf->map[0xd] = 0b100000100000001001;
	wolf->map[0xe] = 0b111111111111111111;
	wolf->map[0xf] = 0;
}

void		map_2(t_wolf *wolf)
{
	wolf->map = (unsigned long *)malloc(sizeof(unsigned long) * 16);
	wolf->map_choice = 31;
	wolf->map[0x0] = 0b11111111111111111111111111111111;
	wolf->map[0x1] = 0b10000000000000100000000000000001;
	wolf->map[0x2] = 0b10000000000000000000000010000001;
	wolf->map[0x3] = 0b10001000000000000000000000000001;
	wolf->map[0x4] = 0b10000000000000000000000000001001;
	wolf->map[0x5] = 0b10000001000000000000000000000001;
	wolf->map[0x6] = 0b10000000000000001000000000000001;
	wolf->map[0x7] = 0b10010000000000000000000000000001;
	wolf->map[0x8] = 0b10000000000000000000000010000001;
	wolf->map[0x9] = 0b10000010000000000000000000000001;
	wolf->map[0xa] = 0b10000000000000100000000000000001;
	wolf->map[0xb] = 0b10000000000000000000010000000001;
	wolf->map[0xc] = 0b10000010000000000000000000000001;
	wolf->map[0xd] = 0b10000000000000010000000000000001;
	wolf->map[0xe] = 0b11111111111111111111111111111111;
	wolf->map[0xf] = 0;
}