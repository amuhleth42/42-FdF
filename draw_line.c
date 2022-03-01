/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:16:20 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/01 17:09:11 by amuhleth         ###   ########.fr       */
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

void	dda(t_game *a, float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	int		i;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabsf(dx) > fabsf(dy))
		steps = fabsf(dx);
	else
		steps = fabsf(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	i = 0;
	while (i <= steps)
	{
		put_pixel_to_img(a->i, x1, y1, 0xFFFFFFFF);
		x1 = x1 + x_inc;
		y1 = y1 + y_inc;
		i++;
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
		dda(a, (float)x1, (float)y1, (float)x, (float)y);
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
