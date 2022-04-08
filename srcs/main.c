/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:40:34 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/08 18:23:30 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop_render(t_fdf *a)
{
	render(a);
	return (0);
}

void	init_mlx_hook(t_fdf *a)
{
	mlx_key_hook(a->win, &key_hook, a);
	mlx_hook(a->win, ON_MOUSEDOWN, 0, &mouse_down, a);
	mlx_hook(a->win, ON_MOUSEUP, 0, &mouse_up, a);
	mlx_hook(a->win, ON_KEYDOWN, 0, &key_down, a);
	mlx_hook(a->win, ON_MOUSEMOVE, 0, &mouse_move, a);
	mlx_hook(a->win, ON_DESTROY, 0, &red_cross, a);
	mlx_loop_hook(a->mlx, &loop_render, a);
	mlx_loop(a->mlx);
}

void	init_cam_position(t_fdf *a)
{
	a->cam.pos.x = 10 * a->map.x;
	a->cam.pos.y = 10 * a->map.x;
	a->cam.pos.z = 10 * a->map.x;
}

void	init_cam(t_fdf *a)
{
	a->cam.scale = 1.0;
	a->cam.altitude = 1.0;
	a->cam.pinhole = 0;
	if (a->map.x >= 50)
		a->cam.p_size = a->map.x * 0.022;
	else
		a->cam.p_size = 1;
	a->cam.rot_z = 0;
	a->cam.offset_x = WIN_WIDTH / 2;
	a->cam.offset_y = WIN_HEIGHT / 2;
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
	parser(argv[1], &a.map, &a);
	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	a.i.img = mlx_new_image(a.mlx, WIN_WIDTH, WIN_HEIGHT);
	a.i.addr = mlx_get_data_addr(a.i.img, &a.i.bpp, &a.i.ll, &a.i.endian);
	init_cam(&a);
	init_cam_position(&a);
	a.mouse.left_down = 0;
	a.mouse.right_down = 0;
	a.mouse.x = 0;
	a.mouse.y = 0;
	world_to_view(&a);
	render(&a);
	init_mlx_hook(&a);
}
