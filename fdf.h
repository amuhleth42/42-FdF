/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:27:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 18:06:38 by amuhleth         ###   ########.fr       */
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

# define SCROLL_UP 4
# define SCROLL_DOWN 5

enum
{
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
	int	color;
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
	t_3d	*map_3d;
	t_3d	*map_2d;
	int		x;
	int		y;
	int		size;
}			t_map;

typedef struct s_cam
{
	double	m[3][3];
	double	view[4][4];
	int		x_cam;
	int		y_cam;
	t_3dv	pos;
	double	scale;
	int	pinhole;
}			t_cam;

typedef struct s_mouse
{
	int	is_down;
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

t_list	*read_file(char *path);
int		check_fdf_format(char *path);
void	parser(char *path, t_map *map);

void	put_pixel_to_img(t_img *i, int x, int y, int color);
void	die(char *s);

void	bresenham(t_fdf *a, t_3d p1, t_3d p2);

void	line_q1(t_fdf *a, t_3d p1, t_3d p2);
void	line_q2(t_fdf *a, t_3d p1, t_3d p2);
void	line_q3(t_fdf *a, t_3d p1, t_3d p2);
void	line_q4(t_fdf *a, t_3d p1, t_3d p2);

int		key_hook(int key, t_fdf *a);
int		mouse_down(int button, int x, int y, t_fdf *a);
int		mouse_up(int button, int x, int y, t_fdf *a);
int		mouse_move(int x, int y, t_fdf *a);

void	draw_map(t_fdf *a, t_3d *map);

void	clear_img(t_img *i);

void	render(t_fdf *a);

#endif
