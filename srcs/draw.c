/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:37:30 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 17:04:13 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_img(t_img *i, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < WIN_WIDTH && 0 <= y && y < WIN_HEIGHT)
	{
		dst = i->addr + (y * i->ll + x * (i->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	compute_delta(t_fdf *a)
{
	int	delta;

	if (a->cam.pinhole)
		delta = (int) pow(1 - log2(a->cam.scale / a->cam.p_size), 1.5);
	else
		delta = (int) pow(1 - log2(a->cam.scale), 1.5);
	if (delta < 1)
		delta = 1;
	return (delta);
}

void	draw_map(t_fdf *a, t_2d *map)
{
	int	i;
	int	j;
	int	delta;

	clear_img(&a->i);
	delta = compute_delta(a);
	j = 0;
	while (j < a->map.y)
	{
		i = 0;
		if (j + delta < a->map.y)
			bresenham(a, map[j * a->map.x + i],
				map[(j + delta) * a->map.x + i]);
		i += delta;
		while (i < a->map.x)
		{
			bresenham(a, map[j * a->map.x + i - delta], map[j * a->map.x + i]);
			if (j + delta < a->map.y)
				bresenham(a, map[j * a->map.x + i],
					map[(j + d) * a->map.x + i]);
			i += delta;
		}
		j += delta;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->i.img, 0, 0);
}
