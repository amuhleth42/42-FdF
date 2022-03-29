/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:46:23 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/29 19:43:37 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_around_z(t_fdf *a, int x)
{
	double	*p[4];
	double	tmp[4][4];
	double	wx;
	double	wy;

	wx = a->cam.dir.x * cos(0.01 * x) - a->cam.dir.y * sin(0.01 * x);
	wy = a->cam.dir.x * sin(0.01 * x) + a->cam.dir.y * cos(0.01 * x);
	p[0] = a->cam.view[0];
	p[1] = a->cam.view[1];
	p[2] = a->cam.view[2];
	p[3] = a->cam.view[3];
	tmp[0][0] = p[0][0];
	tmp[0][1] = p[0][1];
	tmp[0][3] = p[0][3];
	tmp[1][0] = p[1][0];
	tmp[1][1] = p[1][1];
	tmp[1][3] = p[1][3];
	tmp[2][0] = p[2][0];
	tmp[2][1] = p[2][1];
	tmp[2][3] = p[2][3];
	tmp[3][3] = p[3][3];
	p[0][0] = tmp[0][0] * cos(0.01 * x) + tmp[0][1] * sin(0.01 * x);
	p[1][0] = tmp[1][0] * cos(0.01 * x) + tmp[1][1] * sin(0.01 * x);
	p[2][0] = tmp[2][0] * cos(0.01 * x) + tmp[2][1] * sin(0.01 * x);
	p[0][1] = -tmp[0][0] * sin(0.01 * x) + tmp[0][1] * cos(0.01 * x);
	p[1][1] = -tmp[1][0] * sin(0.01 * x) + tmp[1][1] * cos(0.01 * x);
	p[2][1] = -tmp[2][0] * sin(0.01 * x) + tmp[2][1] * cos(0.01 * x);
	//p[0][3] = tmp[0][3] + tmp[0][0] * wx + tmp[0][1] * wy;
	//p[1][3] = tmp[1][3] + tmp[1][0] * wx + tmp[1][1] * wy;
	//p[2][3] = tmp[2][3] + tmp[2][0] * wx + tmp[2][1] * wy;
	//p[3][3] = tmp[3][3] + tmp[3][0] * wx + tmp[3][1] * wy;
	print_matrix(&a->cam);
}
