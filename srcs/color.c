/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:25:06 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/30 17:09:15 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_stock_color(t_map *map, int z)
{
	int	middle_z;

	middle_z = (map->z_max - map->z_min) / 2;
	if (z <= middle_z)
		return (COLOR1);
	else
		return (COLOR2);
}

int	gradient(int c1, int c2, int diff)
{
	double	percent;

	if (diff)
		percent = 1 / diff;
	else
		percent = 1;
	return (c1 + c2 /** percent*/);
}

int	get_color(int c1, int c2, int diff)
{
	int	r;
	int	g;
	int	b;

	r = gradient((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, diff);
	g = gradient((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, diff);
	b = gradient(c1 & 0xFF, c2 & 0xFF, diff);
	return ((r << 16) | (g << 8) | b);
}
