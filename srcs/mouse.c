/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:33:32 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 15:43:40 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_down(int button, int x, int y, t_fdf *a)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
		a->cam.scale *= 1.0 + 0.1;
	if (button == SCROLL_DOWN)
		a->cam.scale *= 1.0 - 0.1;

	if (button == 1)
		a->mouse.is_down = 1;
	render(a);
	return (0);
}

int	mouse_up(int button, int x, int y, t_fdf *a)
{
	(void) x;
	(void) y;
	if (button == 1)
		a->mouse.is_down = 0;
	return (0);
}
/*
int mouse_move(int x, int y, t_fdf *a)
{
}
*/
