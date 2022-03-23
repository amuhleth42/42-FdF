/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:00:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 13:49:41 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham_end(t_fdf *a, t_2d p1, t_2d p2)
{
	int	dx;
	int	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dy > 0)
	{
		if (-dx < dy)
			line_q3(a, p1, p2);
		else
			line_q4(a, p1, p2);
	}
	else
	{
		if (dx < dy)
			line_q1(a, p2, p1);
		else
			line_q2(a, p2, p1);
	}
}

void	bresenham(t_fdf *a, t_2d p1, t_2d p2)
{
	int	dx;
	int	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx > 0)
	{
		if (dy > 0)
		{
			if (dx > dy)
				line_q1(a, p1, p2);
			else
				line_q2(a, p1, p2);
		}
		else
		{
			if (dx < -dy)
				line_q3(a, p2, p1);
			else
				line_q4(a, p2, p1);
		}
	}
	else
		bresenham_end(a, p1, p2);
}
