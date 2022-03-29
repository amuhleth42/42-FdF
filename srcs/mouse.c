/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:33:32 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/29 18:02:51 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	move(t_fdf *a, int x, int y)
{
	a->cam.offset_x += x;
	a->cam.offset_y += y;
}

int	mouse_move(int x, int y, t_fdf *a)
{
	int	dx;
	int	dy;

	a->mouse.lastx = a->mouse.x;
	a->mouse.lasty = a->mouse.y;
	a->mouse.x = x;
	a->mouse.y = y;
	dx = a->mouse.x - a->mouse.lastx;
	dy = a->mouse.y - a->mouse.lasty;
	if (a->mouse.left_down)
		move(a, dx, dy);
	if (a->mouse.right_down)
		rotate_around_z(a, dx);
	if (a->mouse.left_down || a->mouse.right_down)
		render(a);
	return (0);
}

int	mouse_down(int button, int x, int y, t_fdf *a)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
	{
		a->cam.scale *= 1.0 + 0.1;
		printf("Scale : %f\n", a->cam.scale);
	}
	if (button == SCROLL_DOWN)
	{
		a->cam.scale *= 1.0 - 0.1;
		printf("Scale : %f\n", a->cam.scale);
	}
	if (button == LEFT)
		a->mouse.left_down = 1;
	if (button == RIGHT)
		a->mouse.right_down = 1;
	render(a);
	return (0);
}

int	mouse_up(int button, int x, int y, t_fdf *a)
{
	(void) x;
	(void) y;
	if (button == LEFT)
		a->mouse.left_down = 0;
	if (button == RIGHT)
		a->mouse.right_down = 0;
	return (0);
}
