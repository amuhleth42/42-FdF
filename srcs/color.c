/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:25:06 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/12 15:58:22 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_point_color(t_map *map, int z, int c1, int c2)
{
	float	shade;

	shade = (float)(z - map->z_min) / (map->z_max - map->z_min);
	return (get_color(c1, c2, shade));
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

void	color_map(t_map *map, int c1, int c2)
{
	int	i;

	i = 0;
	while (i < map->size)
	{
		map->map_2d[i].color = set_point_color(map, map->world[i].z, c1, c2);
		i++;
	}
}

void	change_color_set(t_fdf *a)
{
	static int	i;

	i++;
	if (i % 10 == 0)
		color_map(&a->map, C3, C4);
	if (i % 10 == 1)
		color_map(&a->map, C2, C1);
	if (i % 10 == 2)
		color_map(&a->map, C1, C2);
	if (i % 10 == 3)
		color_map(&a->map, C4, C3);
	if (i % 10 == 4)
		color_map(&a->map, C1, C4);
	if (i % 10 == 5)
		color_map(&a->map, C2, C3);
	if (i % 10 == 6)
		color_map(&a->map, C5, C6);
	if (i % 10 == 7)
		color_map(&a->map, C3, C6);
	if (i % 10 == 8)
		color_map(&a->map, C4, C6);
	if (i % 10 == 9)
		color_map(&a->map, C2, C6);
}
