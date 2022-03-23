/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:40:34 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 19:02:52 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	render_point(t_cam cam, t_3d *p, t_3d *p_2d)
{
	p_2d->x = cam.x_cam + cam.scale * (cam.m[0][0] * p->x + cam.m[0][1] * p->y + cam.m[0][2] * p->z + );
	p_2d->y = cam.y_cam + cam.scale * (cam.m[1][0] * p->x + cam.m[1][1] * p->y + cam.m[1][2] * p->z);
	p_2d->z = cam.scale * (cam.m[2][0] * p->x + cam.m[2][1] * p->y + cam.m[2][2] * p->z);
}*/

void	perspective_divide(t_3d *p)
{
	if (p->z)
	{
		p->x = p->x * WIN_WIDTH / 2 / (p->z + WIN_WIDTH / 2);
		p->y = p->y * WIN_HEIGHT / 2 / (p->z + WIN_HEIGHT / 2);
	}
}


void	point_in_view(t_cam cam, t_3d *p, t_3d *p_2d)
{
	p_2d->x = 1 * (cam.view[0][0] * p->x + cam.view[0][1] * p->y + cam.view[0][2] * p->z + cam.view[0][3]);
	p_2d->y = 1 * (cam.view[1][0] * p->x + cam.view[1][1] * p->y + cam.view[1][2] * p->z + cam.view[1][3]);
	p_2d->z = 1 * (cam.view[2][0] * p->x + cam.view[2][1] * p->y + cam.view[2][2] * p->z + cam.view[2][3]);
}

void	zoom(t_fdf *a, t_3d *p_2d)
{
	p_2d->x *= a->cam.scale;
	p_2d->y *= a->cam.scale;
	p_2d->z *= a->cam.scale;
}

t_3dv	normalize(t_3dv v)
{
	t_3dv	res;
	double	len2;
	double	inv_len;

	len2 = v.x * v.x + v.y * v.y + v.z * v.z;
	if (len2 > 0)
	{
		inv_len = 1 / sqrt(len2);
		res.x = v.x * inv_len;
		res.y = v.y * inv_len;
		res.z = v.z * inv_len;
	}
	else
	{
		res.x = v.x;
		res.y = v.y;
		res.z = v.z;
	}
	return (res);

}

t_3dv	cross_product(t_3dv a, t_3dv b)
{
	t_3dv	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

void	fourth_row(t_fdf *a, t_3dv *pos)
{
	double	*s;
	double	*u;
	double	*f;

	s = a->cam.view[0];
	u = a->cam.view[1];
	f = a->cam.view[2];
	a->cam.view[3][0] = -pos->x * s[0] - pos->y * s[1] - pos->z * s[2];
	a->cam.view[3][1] = -pos->x * u[0] - pos->y * u[1] - pos->z * u[2];
	a->cam.view[3][2] = -pos->x * f[0] - pos->y * f[1] - pos->z * f[2];
}

void	world_to_view(t_fdf *a)
{
	t_3dv	f;
	t_3dv	s;
	t_3dv	up;
	t_3dv	u;

	up.x = 0;
	up.y = 0;
	up.z = -1;
	f = normalize(a->cam.pos);
	s = cross_product(f, normalize(up));
	u = cross_product(s, f);
	a->cam.view[0][0] = -s.x;
	a->cam.view[0][1] = -s.y;
	a->cam.view[0][2] = -s.z;
	a->cam.view[1][0] = u.x;
	a->cam.view[1][1] = u.y;
	a->cam.view[1][2] = u.z;
	a->cam.view[2][0] = -f.x;
	a->cam.view[2][1] = -f.y;
	a->cam.view[2][2] = -f.z;
	fourth_row(a, &a->cam.pos);
}

void	offset_point(t_3d *p)
{
	p->x += WIN_WIDTH / 2;
	p->y += WIN_HEIGHT / 2;
}

void	render(t_fdf *a)
{
	int	i;

	clear_img(&a->i);
	i = 0;
	a->map.map_2d = ft_calloc(a->map.size + 1, sizeof(t_3d));
	while (i < a->map.size)
	{
		point_in_view(a->cam, &a->map.map_3d[i], &a->map.map_2d[i]);
		if (a->cam.pinhole)
			perspective_divide(&a->map.map_2d[i]);
		zoom(a, &a->map.map_2d[i]);
		offset_point(&a->map.map_2d[i]);
		i++;
	}
	draw_map(a, a->map.map_2d);
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
	a.cam.m[2][0] = sqrt(2);
	a.cam.m[2][1] = -sqrt(2);
	a.cam.m[2][2] = sqrt(2);
	a.cam.scale = 1.0;
	a.cam.pinhole = 0;
	a.cam.x_cam = WIN_WIDTH / 2;
	a.cam.y_cam = WIN_HEIGHT / 2;
	a.cam.pos.x = 2 * a.map.x;
	a.cam.pos.y = 2 * a.map.x;
	a.cam.pos.z = 20;
	world_to_view(&a);
	render(&a);
	print_map2d(a.map.map_2d, a.map.size);
	//draw_map(&a, a.map.map_2d);
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_hook(a.win, ON_MOUSEDOWN, 0, &mouse_down, &a);
	mlx_hook(a.win, ON_MOUSEUP, 0, &mouse_up, &a);
	//mlx_hook(a.win, ON_MOUSEMOVE, 0, &mouse_move, &a);
	mlx_loop(a.mlx);
}
