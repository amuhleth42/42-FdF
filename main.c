/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:40:34 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/09 14:49:40 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int key, t_fdf *a)
{
	if (key == 53)
	{
		mlx_destroy_window(a->mlx, a->win);
		free(a->i);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	draw_line(t_fdf *a, int x, int y)
{
	static int	i;
	static t_2d	p1;
	t_2d		p2;

	if (i == 0)
	{
		i++;
		p1.x = x;
		p1.y = y;
	}
	else
	{
		i--;
		p2.x = x;
		p2.y = y;
		bresenham(a, p1, p2);
	}
}

int	mouse_hook(int button, int x, int y, t_fdf *a)
{
	if (button == 1)
	{
		draw_line(a, x, y);
		mlx_put_image_to_window(a->mlx, a->win, a->i->img, 0, 0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf a;

	(void) argv;
	if (argc != 2)
	{
		ft_printf("Error\n");
		return (1);
	}
	parser(argv[1], &a.map);
	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, 1000, 1000, "Draw_line");
	a.i = ft_calloc(1, sizeof(t_img));
	a.i->img = mlx_new_image(a.mlx, 1000, 1000);
	a.i->addr = mlx_get_data_addr(a.i->img, &a.i->bpp, &a.i->ll, &a.i->endian);

	mlx_key_hook(a.win, &key_hook, &a);
	mlx_mouse_hook(a.win, &mouse_hook, &a);
	mlx_loop(a.mlx);
}
