/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:00:15 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/26 15:45:15 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_q1(t_fdf *a, t_2d p1, t_2d p2)
{
	int	dx;
	int	dy;
	int	p;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	p = 2 * dy - dx;
	while (p1.x <= p2.x)
	{
		put_pixel_to_img(&a->i, p1.x, p1.y, get_color(p1.color, p2.color));
		p1.x++;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p = p + (2 * dy) - (2 * dx);
			p1.y++;
		}
	}
}

void	line_q2(t_fdf *a, t_2d p1, t_2d p2)
{
	int	dx;
	int	dy;
	int	p;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	p = 2 * dx - dy;
	while (p1.y <= p2.y)
	{
		put_pixel_to_img(&a->i, p1.x, p1.y, get_color(p1.color, p2.color));
		p1.y++;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p = p + (2 * dx) - (2 * dy);
			p1.x++;
		}
	}
}

void	line_q3(t_fdf *a, t_2d p1, t_2d p2)
{
	int	dx;
	int	dy;
	int	p;

	dx = abs(p2.x - p1.x);
	dy = p2.y - p1.y;
	p = 2 * dx - dy;
	while (p1.y <= p2.y)
	{
		put_pixel_to_img(&a->i, p1.x, p1.y, get_color(p1.color, p2.color));
		p1.y++;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p = p + (2 * dx) - (2 * dy);
			p1.x--;
		}
	}
}

void	line_q4(t_fdf *a, t_2d p1, t_2d p2)
{
	int	dx;
	int	dy;
	int	p;

	dx = abs(p2.x - p1.x);
	dy = p2.y - p1.y;
	p = 2 * dy - dx;
	while (p1.x >= p2.x)
	{
		put_pixel_to_img(&a->i, p1.x, p1.y, get_color(p1.color, p2.color));
		p1.x--;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p = p + (2 * dy) - (2 * dx);
			p1.y++;
		}
	}
}
