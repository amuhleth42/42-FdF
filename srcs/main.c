/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:40:34 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 16:19:22 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	perspective_divide(t_3dv *p)
{
	if (p->z + WIN_WIDTH && p->z + WIN_HEIGHT)
	{
		p->x = p->x * WIN_WIDTH / (p->z + WIN_WIDTH);
		p->y = p->y * WIN_HEIGHT / (p->z + WIN_HEIGHT);
	}
}

void	point_in_view(t_cam cam, t_3d *p, t_3dv *render)
{
	render->x = cam.view[0][0] * p->x + cam.view[0][1] * p->y
		+ cam.view[0][2] * p->z * cam.altitude + cam.view[0][3];
	render->y = cam.view[1][0] * p->x + cam.view[1][1] * p->y
		+ cam.view[1][2] * p->z * cam.altitude + cam.view[1][3];
	render->z = cam.view[2][0] * p->x + cam.view[2][1] * p->y
		+ cam.view[2][2] * p->z * cam.altitude + cam.view[2][3];
}

void	zoom(t_fdf *a, t_3dv *p)
{
	p->x *= a->cam.scale;
	p->y *= a->cam.scale;
	p->z *= a->cam.scale;
}

void	offset_point(t_3dv *p, t_2d *p_2d, t_fdf *a)
{
	p_2d->x = floor(p->x) + a->cam.offset_x;
	p_2d->y = floor(p->y) + a->cam.offset_y;
}

void	render(t_fdf *a)
{
	int	i;

	i = 0;
	if (a->cam.rot_z)
	{
		usleep(200);
		rotate_around_z(a, 1);
	}
	while (i < a->map.size)
	{
		point_in_view(a->cam, &a->map.world[i], &a->map.render[i]);
		if (a->cam.pinhole)
			perspective_divide(&a->map.render[i]);
		zoom(a, &a->map.render[i]);
		offset_point(&a->map.render[i], &a->map.map_2d[i], a);
		i++;
	}
	draw_map(a, a->map.map_2d);
}

int	loop_render(t_fdf *a)
{
	render(a);
	return (0);
}

void	print_map2d(t_3d *map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("2d : x: %d", map[i].x);
		ft_printf(", y: %d", map[i].y);
		ft_printf(", z: %d\n", map[i].z);
		i++;
	}
}

void	init_mlx_hook(t_fdf *a)
{
	mlx_key_hook(a->win, &key_hook, a);
	mlx_hook(a->win, ON_MOUSEDOWN, 0, &mouse_down, a);
	mlx_hook(a->win, ON_MOUSEUP, 0, &mouse_up, a);
	mlx_hook(a->win, ON_KEYDOWN, 0, &key_down, a);
	mlx_hook(a->win, ON_MOUSEMOVE, 0, &mouse_move, a);
	mlx_loop_hook(a->mlx, &loop_render, a);
	mlx_loop(a->mlx);
}

void	init_cam_position(t_fdf *a)
{
	a->cam.pos.x = 10 * a->map.x;
	a->cam.pos.y = 10 * a->map.x;
	a->cam.pos.z = 10 * a->map.x;
}

int	main(int argc, char **argv)
{
	t_fdf	a;

	(void) argv;
	if (argc != 2)
	{
		ft_printf("Error\n");
		return (1);
	}
	a.map.z_min = 0;
	a.map.z_max = 0;
	parser(argv[1], &a.map);
	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	a.i.img = mlx_new_image(a.mlx, WIN_WIDTH, WIN_HEIGHT);
	a.i.addr = mlx_get_data_addr(a.i.img, &a.i.bpp, &a.i.ll, &a.i.endian);
	a.cam.scale = 1.0;
	a.cam.altitude = 1.0;
	a.cam.pinhole = 0;
	if (a.map.x >= 50)
		a.cam.p_size = a.map.x * 0.022;
	else
		a.cam.p_size = 1;
	a.cam.rot_z = 0;
	a.cam.offset_x = WIN_WIDTH / 2;
	a.cam.offset_y = WIN_HEIGHT / 2;
	init_cam_position(&a);
	a.mouse.left_down = 0;
	a.mouse.right_down = 0;
	a.mouse.x = 0;
	a.mouse.y = 0;
	world_to_view(&a);
	render(&a);
	init_mlx_hook(&a);
}
