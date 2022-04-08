
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:27:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/08 18:03:54 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define COLOR1 0xFF2C3C
# define COLOR2 0xB166E1
# define LEFT 1
# define RIGHT 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5

enum
{
	ON_KEYDOWN = 2,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6
};

typedef struct s_2d
{
	int	x;
	int	y;
	int	color;
}		t_2d;

typedef struct s_3dv
{
	double	x;
	double	y;
	double	z;
}			t_3dv;

typedef struct s_3d
{
	int	x;
	int	y;
	int	z;
}		t_3d;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}			t_img;

typedef struct s_map
{
	t_3d	*world;
	t_3dv	*render;
	t_2d	*map_2d;
	int		x;
	int		y;
	int		size;
	int		z_min;
	int		z_max;
}			t_map;

typedef struct s_cam
{
	double	view[4][4];
	int		offset_x;
	int		offset_y;
	t_3dv	pos;
	double	scale;
	double	altitude;
	int		pinhole;
	double	p_size;
	int		rot_z;
}			t_cam;

typedef struct s_mouse
{
	int	left_down;
	int	right_down;
	int	x;
	int	y;
	int	lastx;
	int	lasty;
}		t_mouse;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	i;
	t_map	map;
	t_cam	cam;
	t_mouse	mouse;
}			t_fdf;

void	parser(char *path, t_map *map, t_fdf *a);

void	die(char *s);
void	switch_bool(int *b);

void	bresenham(t_fdf *a, t_2d p1, t_2d p2);

void	line_q1(t_fdf *a, t_2d p1, t_2d p2);
void	line_q2(t_fdf *a, t_2d p1, t_2d p2);
void	line_q3(t_fdf *a, t_2d p1, t_2d p2);
void	line_q4(t_fdf *a, t_2d p1, t_2d p2);

int		key_hook(int key, t_fdf *a);
int		key_down(int key, t_fdf *a);
int		mouse_down(int button, int x, int y, t_fdf *a);
int		mouse_up(int button, int x, int y, t_fdf *a);
int		mouse_move(int x, int y, t_fdf *a);

void	put_pixel_to_img(t_img *i, int x, int y, int color);
void	draw_map(t_fdf *a, t_2d *map);

void	clear_img(t_img *i);
void	exit_all(t_fdf *a);
void	free_maps(t_fdf *a);

void	render(t_fdf *a);

void	world_to_view(t_fdf *a);
t_3dv	normalize(t_3dv v);
void	print_matrix(t_cam *cam);

int		set_point_color(t_map *map, int z);
void	color_map(t_map *map);
int		get_color(int c1, int c2, float shade);

void	rotate_around_z(t_fdf *a, int x);
void	rotate_around_y(t_fdf *a, int x);
void	rotate_around_x(t_fdf *a, int x, int y);

#endif
