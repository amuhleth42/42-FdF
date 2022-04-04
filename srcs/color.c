/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:25:06 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/04 19:29:57 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	set_point_color(t_map *map, int z)
{
	float	shade;

	shade = (float)(z - map->z_min) / (map->z_max - map->z_min);
	return (get_color(COLOR1, COLOR2, shade));
}

int	mix_color(int c1, int c2, float shade)
{
	return (c1 - shade * c1 + shade * c2);
}

int	get_color(int c1, int c2, float shade)
{
	int	r;
	int	g;
	int	b;

	r = mix_color(c1 >> 16 & 0xFF, c2 >> 16 & 0xFF, shade);
	g = mix_color(c1 >> 8 & 0xFF, c2 >> 8 & 0xFF, shade);
	b = mix_color(c1 & 0xFF, c2 & 0xFF, shade);
	return (r << 16 | g << 8 | b);
}

void	color_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size)
	{
		map->map_2d[i].color = set_point_color(map, map->world[i].z);
		i++;
	}
}
