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
		mlx_put_image_to_window(a->mlx, a->win, a->i.img, 0, 0);
	}
	return (0);
}

void	render_point(t_cam cam, t_3d *p, t_2d *p_2d)
{
	p_2d->x = cam.x_cam + cam.m[0][0] * p->x + cam.m[0][1] * p->y + cam.m[0][2] * p->z;
	p_2d->y = cam.y_cam + cam.m[1][0] * p->x + cam.m[1][1] * p->y + cam.m[1][2] * p->z;
}

void	rendering(t_fdf *a)
{
	int	i;

	i = 0;
	a->map.map_2d = ft_calloc(a->map.size, sizeof(t_2d));
	while (i < a->map.size)
	{
		render_point(a->cam, &a->map.map_3d[i], &a->map.map_2d[i]);
		i++;
	}
}

void	print_map2d(t_2d *map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("2d : x: %d", map[i].x);
		ft_printf(", y: %d\n", map[i].y);
		i++;
	}
}

void	draw_map(t_fdf *a, t_2d *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < a->map.y)
	{
		i = 0;
		if (j + 1 < a->map.y)
			bresenham(a, map[j * a->map.x + i], map[(j + 1) * a->map.x + i]);
		while (++i < a->map.x)
		{
			bresenham(a, map[j * a->map.x + i - 1], map[j * a->map.x + i]);
			if (j + 1 < a->map.y)
				bresenham(a, map[j * a->map.x + i], map[(j + 1) * a->map.x + i]);
		}
		j++;
	}
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
	a.win = mlx_new_window(a.mlx, WIN_WIDTH, WIN_HEIGHT, "Draw_line");
	a.i.img = mlx_new_image(a.mlx, WIN_WIDTH, WIN_HEIGHT);
	a.i.addr = mlx_get_data_addr(a.i.img, &a.i.bpp, &a.i.ll, &a.i.endian);

	a.cam.m[0][0] = sqrt(3);
	a.cam.m[0][1] = -sqrt(3);
	a.cam.m[0][2] = 0.0;
	a.cam.m[1][0] = 1.0;
	a.cam.m[1][1] = 1.0;
	a.cam.m[1][2] = -2.0;
	a.cam.x_cam = WIN_WIDTH / 2;
	a.cam.y_cam = WIN_HEIGHT / 2;
	rendering(&a);
	print_map2d(a.map.map_2d, a.map.size);
	draw_map(&a, a.map.map_2d);
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_mouse_hook(a.win, &mouse_hook, &a);
	mlx_loop(a.mlx);
}
