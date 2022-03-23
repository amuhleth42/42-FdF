/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:40:34 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 15:30:38 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_point(t_cam cam, t_3d *p, t_2d *p_2d)
{
	p_2d->x = cam.x_cam + cam.scale * (cam.m[0][0] * p->x + cam.m[0][1] * p->y + cam.m[0][2] * p->z);
	p_2d->y = cam.y_cam + cam.scale * (cam.m[1][0] * p->x + cam.m[1][1] * p->y + cam.m[1][2] * p->z);
}

void	render(t_fdf *a)
{
	int	i;

	clear_img(&a->i);
	i = 0;
	a->map.map_2d = ft_calloc(a->map.size + 1, sizeof(t_2d));
	while (i < a->map.size)
	{
		render_point(a->cam, &a->map.map_3d[i], &a->map.map_2d[i]);
		i++;
	}
	draw_map(a, a->map.map_2d);
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
	a.cam.scale = 1.0;
	a.cam.x_cam = WIN_WIDTH / 2;
	a.cam.y_cam = WIN_HEIGHT / 2;
	render(&a);
	print_map2d(a.map.map_2d, a.map.size);
	//draw_map(&a, a.map.map_2d);
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_hook(a.win, ON_MOUSEDOWN, 0, &mouse_down, &a);
	mlx_hook(a.win, ON_MOUSEUP, 0, &mouse_up, &a);
	//mlx_hook(a.win, ON_MOUSEMOVE, 0, &mouse_move, &a);
	mlx_loop(a.mlx);
}