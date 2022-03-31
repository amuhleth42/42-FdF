/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:39:00 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 16:39:12 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	perspective_divide(t_3dv *p)
{
	if (p->z + WIN_WIDTH && p->z + WIN_HEIGHT)
	{
		p->x = p->x * WIN_WIDTH / (p->z + WIN_WIDTH);
		p->y = p->y * WIN_HEIGHT / (p->z + WIN_HEIGHT);
	}
}

void	point_in_view(t_cam cam, t_3d *p, t_3dv *render)
{
	render->x = cam.view[0][0] * p->x + cam.view[0][1] * p->y
		+ cam.view[0][2] * p->z * cam.altitude + cam.view[0][3];
	render->y = cam.view[1][0] * p->x + cam.view[1][1] * p->y
		+ cam.view[1][2] * p->z * cam.altitude + cam.view[1][3];
	render->z = cam.view[2][0] * p->x + cam.view[2][1] * p->y
		+ cam.view[2][2] * p->z * cam.altitude + cam.view[2][3];
}

void	zoom(t_fdf *a, t_3dv *p)
{
	p->x *= a->cam.scale;
	p->y *= a->cam.scale;
	p->z *= a->cam.scale;
}

void	offset_point(t_3dv *p, t_2d *p_2d, t_fdf *a)
{
	p_2d->x = floor(p->x) + a->cam.offset_x;
	p_2d->y = floor(p->y) + a->cam.offset_y;
}

void	render(t_fdf *a)
{
	int	i;

	i = 0;
	if (a->cam.rot_z)
	{
		usleep(200);
		rotate_around_z(a, 1);
	}
	while (i < a->map.size)
	{
		point_in_view(a->cam, &a->map.world[i], &a->map.render[i]);
		if (a->cam.pinhole)
			perspective_divide(&a->map.render[i]);
		zoom(a, &a->map.render[i]);
		offset_point(&a->map.render[i], &a->map.map_2d[i], a);
		i++;
	}
	draw_map(a, a->map.map_2d);
}
