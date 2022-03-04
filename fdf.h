/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:27:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/04 20:42:23 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>

# define MAX_LINE 1000
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_2dpoint
{
	int	x;
	int	y;
	int	color;
}		t_2dpoint;

typedef struct s_3dpoint
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_3dpoint;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}			t_img;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	*i;
}			t_fdf;

char	**read_file(char *path);
int		check_fdf_format(char *path);

void	put_pixel_to_img(t_img *i, int x, int y, int color);

void	bresenham(t_fdf *a, t_2dpoint p1, t_2dpoint p2);

void	line_q1(t_fdf *a, t_2dpoint p1, t_2dpoint p2);
void	line_q2(t_fdf *a, t_2dpoint p1, t_2dpoint p2);
void	line_q3(t_fdf *a, t_2dpoint p1, t_2dpoint p2);
void	line_q4(t_fdf *a, t_2dpoint p1, t_2dpoint p2);

#endif
