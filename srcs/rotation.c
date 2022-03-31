/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:46:23 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 16:22:30 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_around_z(t_fdf *a, int x)
{
	double	*p[3];
	double	tmp[3][4];

	p[0] = a->cam.view[0];
	p[1] = a->cam.view[1];
	p[2] = a->cam.view[2];
	tmp[0][0] = p[0][0];
	tmp[0][1] = p[0][1];
	tmp[1][0] = p[1][0];
	tmp[1][1] = p[1][1];
	tmp[2][0] = p[2][0];
	tmp[2][1] = p[2][1];
	p[0][0] = tmp[0][0] * cos(0.01 * x) + tmp[0][1] * sin(0.01 * x);
	p[1][0] = tmp[1][0] * cos(0.01 * x) + tmp[1][1] * sin(0.01 * x);
	p[2][0] = tmp[2][0] * cos(0.01 * x) + tmp[2][1] * sin(0.01 * x);
	p[0][1] = -tmp[0][0] * sin(0.01 * x) + tmp[0][1] * cos(0.01 * x);
	p[1][1] = -tmp[1][0] * sin(0.01 * x) + tmp[1][1] * cos(0.01 * x);
	p[2][1] = -tmp[2][0] * sin(0.01 * x) + tmp[2][1] * cos(0.01 * x);
}

void	rotate_around_y(t_fdf *a, int x)
{
	double	*p[3];
	double	tmp[3][4];

	p[0] = a->cam.view[0];
	p[1] = a->cam.view[1];
	p[2] = a->cam.view[2];
	tmp[0][0] = p[0][0];
	tmp[0][2] = p[0][2];
	tmp[1][0] = p[1][0];
	tmp[1][2] = p[1][2];
	tmp[2][0] = p[2][0];
	tmp[2][2] = p[2][2];
	p[0][0] = tmp[0][0] * cos(0.005 * x) - tmp[0][2] * sin(0.005 * x);
	p[1][0] = tmp[1][0] * cos(0.005 * x) - tmp[1][2] * sin(0.005 * x);
	p[2][0] = tmp[2][0] * cos(0.005 * x) - tmp[2][2] * sin(0.005 * x);
	p[0][2] = tmp[0][0] * sin(0.005 * x) + tmp[0][2] * cos(0.005 * x);
	p[1][2] = tmp[1][0] * sin(0.005 * x) + tmp[1][2] * cos(0.005 * x);
	p[2][2] = tmp[2][0] * sin(0.005 * x) + tmp[2][2] * cos(0.005 * x);
}

void	rotate_around_x(t_fdf *a, int x, int y)
{
	double	*p[3];
	double	tmp[3][4];

	p[0] = a->cam.view[0];
	p[1] = a->cam.view[1];
	p[2] = a->cam.view[2];
	tmp[0][1] = p[0][1];
	tmp[0][2] = p[0][2];
	tmp[1][1] = p[1][1];
	tmp[1][2] = p[1][2];
	tmp[2][1] = p[2][1];
	tmp[2][2] = p[2][2];
	p[0][1] = tmp[0][1] * cos(0.005 * x) + tmp[0][2] * sin(0.005 * x);
	p[1][1] = tmp[1][1] * cos(0.005 * x) + tmp[1][2] * sin(0.005 * x);
	p[2][1] = tmp[2][1] * cos(0.005 * x) + tmp[2][2] * sin(0.005 * x);
	p[0][2] = -tmp[0][1] * sin(0.005 * x) + tmp[0][2] * cos(0.005 * x);
	p[1][2] = -tmp[1][1] * sin(0.005 * x) + tmp[1][2] * cos(0.005 * x);
	p[2][2] = -tmp[2][1] * sin(0.005 * x) + tmp[2][2] * cos(0.005 * x);
	rotate_around_y(a, y);
}
