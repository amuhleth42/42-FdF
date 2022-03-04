/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:00:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/04 18:02:07 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham_end(t_game *a, t_2dpoint p1, t_2dpoint p2)
{
	int	dx;
	int	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dy > 0) //q3, q4
	{
		if (-dx < dy)
			line_q3(a, p1, p2);
		else
			line_q4(a, p1, p2);
	}
	else //q5, q6
	{
		if (dx < dy)
			line_q1(a, p2, p1);
		else
			line_q2(a, p2, p1);
	}
}

void	bresenham(t_game *a, t_2dpoint p1, t_2dpoint p2)
{
	int	dx;
	int	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx > 0)
	{
		if (dy > 0) //q1, q2
		{
			if (dx > dy)
				line_q1(a, p1, p2);
			else
				line_q2(a, p1, p2);
		}
		else //q7, q8
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
