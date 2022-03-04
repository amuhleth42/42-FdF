/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:27:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/04 18:03:35 by amuhleth         ###   ########.fr       */
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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	*i;
}			t_game;

char	**read_file(char *path);

void	put_pixel_to_img(t_img *i, int x, int y, int color);

void	bresenham(t_game *a, t_2dpoint p1, t_2dpoint p2);

void	line_q1(t_game *a, t_2dpoint p1, t_2dpoint p2);
void	line_q2(t_game *a, t_2dpoint p1, t_2dpoint p2);
void	line_q3(t_game *a, t_2dpoint p1, t_2dpoint p2);
void	line_q4(t_game *a, t_2dpoint p1, t_2dpoint p2);
#endif
