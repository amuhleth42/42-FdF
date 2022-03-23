/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:37:30 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 13:37:56 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_fdf *a, t_2d *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < a->map.y)
	{
		i = 0;
		if (j + 1 < a->map.y)
			bresenham(a, map[j * a->map.x + i], map[(j + 1) * a->map.x + i]);
		while (++i < a->map.x)
		{
			bresenham(a, map[j * a->map.x + i - 1], map[j * a->map.x + i]);
			if (j + 1 < a->map.y)
				bresenham(a, map[j * a->map.x + i], map[(j + 1) * a->map.x + i]);
		}
		j++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->i.img, 0, 0);
}
