/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:02:01 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/12 16:59:28 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_3dv	normalize(t_3dv v)
{
	t_3dv	res;
	double	len2;
	double	inv_len;

	len2 = v.x * v.x + v.y * v.y + v.z * v.z;
	if (len2 > 0)
	{
		inv_len = 1 / sqrt(len2);
		res.x = v.x * inv_len;
		res.y = v.y * inv_len;
		res.z = v.z * inv_len;
	}
	else
	{
		res.x = v.x;
		res.y = v.y;
		res.z = v.z;
	}
	return (res);
}

t_3dv	cross_product(t_3dv a, t_3dv b)
{
	t_3dv	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

void	fourth_row(t_fdf *a, t_3dv *pos)
{
	double	*s;
	double	*u;
	double	*f;

	s = a->cam.view[0];
	u = a->cam.view[1];
	f = a->cam.view[2];
	a->cam.view[0][3] = -pos->x * s[0] - pos->y * s[1] - pos->z * s[2];
	a->cam.view[1][3] = -pos->x * u[0] - pos->y * u[1] - pos->z * u[2];
	a->cam.view[2][3] = -pos->x * f[0] - pos->y * f[1] - pos->z * f[2];
}

void	print_matrix(t_cam *cam)
{
	printf("%f  ", cam->view[0][0]);
	printf("%f  ", cam->view[0][1]);
	printf("%f  ", cam->view[0][2]);
	printf("%f\n", cam->view[0][3]);
	printf("%f  ", cam->view[1][0]);
	printf("%f  ", cam->view[1][1]);
	printf("%f  ", cam->view[1][2]);
	printf("%f\n", cam->view[1][3]);
	printf("%f  ", cam->view[2][0]);
	printf("%f  ", cam->view[2][1]);
	printf("%f  ", cam->view[2][2]);
	printf("%f\n", cam->view[2][3]);
	printf("%f  ", cam->view[3][0]);
	printf("%f  ", cam->view[3][1]);
	printf("%f  ", cam->view[3][2]);
	printf("%f\n", cam->view[3][3]);
}

void	world_to_view(t_fdf *a)
{
	t_3dv	f;
	t_3dv	s;
	t_3dv	up;
	t_3dv	u;

	up.x = 0;
	up.y = 0;
	up.z = -1;
	f = a->cam.pos;
	f = normalize(f);
	s = cross_product(f, normalize(up));
	u = cross_product(s, f);
	a->cam.view[0][0] = -s.x;
	a->cam.view[0][1] = -s.y;
	a->cam.view[0][2] = -s.z;
	a->cam.view[1][0] = u.x;
	a->cam.view[1][1] = u.y;
	a->cam.view[1][2] = u.z;
	a->cam.view[2][0] = -f.x;
	a->cam.view[2][1] = -f.y;
	a->cam.view[2][2] = -f.z;
	fourth_row(a, &a->cam.pos);
}
