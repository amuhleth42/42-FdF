/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:10:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/01 19:12:54 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_line.h"

void	put_pixel_to_img(t_img *i, int x, int y, int color)
{
	char	*dst;

	dst = i->addr + (y * i->ll + x * (i->bpp / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int key, t_game *a)
{
	if (key == 53)
	{
		mlx_destroy_window(a->mlx, a->win);
		free(a->i);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	line_q1(t_game *a, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	p;
	int	i;

	dx = x2 - x1;
	dy = y2 - y1;
	p = 2 * dx - dy;
	i = 0;
	while (x1 <= x2)
	{
		put_pixel_to_img(a->i, x1, y1, 0xFFFFFFFF);
		x1++;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p = p + (2 * dy) - (2 * dx);
			y1++;
		}
	}
}

void	line_q2(t_game *a, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	p;
	int	i;

	dx = x2 - x1;
	dy = y2 - y1;
	p = 2 * dy - dx;
	i = 0;
	while (y1 <= y2)
	{
		put_pixel_to_img(a->i, x1, y1, 0xFFFFFFFF);
		y1++;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p = p + (2 * dx) - (2 * dy);
			x1++;
		}
	}
}

void	line_q3(t_game *a, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	p;
	int	i;

	dx = abs(x2 - x1);
	dy = y2 - y1;
	p = 2 * dy - dx;
	i = 0;
	while (y1 <= y2)
	{
		put_pixel_to_img(a->i, x1, y1, 0xFFFFFFFF);
		y1++;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p = p + (2 * dx) - (2 * dy);
			x1--;
		}
	}
}

void	line_q4(t_game *a, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	p;
	int	i;

	dx = abs(x2 - x1);
	dy = y2 - y1;
	p = 2 * dx - dy;
	i = 0;
	while (x1 >= x2)
	{
		put_pixel_to_img(a->i, x1, y1, 0xFFFFFFFF);
		x1--;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p = p + (2 * dy) - (2 * dx);
			y1++;
		}
	}
}

void	bresenham(t_game *a, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	if (dx > 0)
	{
		if (dy > 0) //q1, q2
		{
			if (dx > dy)
				line_q1(a, x1, y1, x2, y2);
			else
				line_q2(a, x1, y1, x2, y2);
		}
		else //q7, q8
		{
			if (dx < -dy)
				line_q3(a, x2, y2, x1, y1);
			else
				line_q4(a, x2, y2, x1, y1);
		}
	}
	else
	{
		if (dy > 0) //q3, q4
		{
			if (-dx < dy)
				line_q3(a, x1, y1, x2, y2);
			else
				line_q4(a, x1, y1, x2, y2);
		}
		else //q5, q6
		{
			if (dx < dy)
				line_q1(a, x2, y2, x1, y1);
			else
				line_q2(a, x2, y2, x1, y1);
		}
	}
}

void	draw_line(t_game *a, int x, int y)
{
	static int	i;
	static int	x1;
	static int	y1;

	if (i == 0)
	{
		i++;
		x1 = x;
		y1 = y;
	}
	else
	{
		i--;
		bresenham(a, x1, y1, x, y);
	}
}

int	mouse_hook(int button, int x, int y, t_game *a)
{
	if (button == 1)
	{
		draw_line(a, x, y);
		mlx_put_image_to_window(a->mlx, a->win, a->i->img, 0, 0);
	}
	return (0);
}

int	main(void)
{
	t_game a;

	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, 1000, 1000, "Draw_line");
	a.i = ft_calloc(1, sizeof(t_img));
	a.i->img = mlx_new_image(a.mlx, 1000, 1000);
	a.i->addr = mlx_get_data_addr(a.i->img, &a.i->bpp, &a.i->ll, &a.i->endian);
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_mouse_hook(a.win, &mouse_hook, &a);
	mlx_loop(a.mlx);
}
