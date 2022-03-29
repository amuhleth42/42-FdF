/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:30:51 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/29 16:56:57 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	key_hook(int key, t_fdf *a)
{
	if (key == 53)
	{
		mlx_destroy_window(a->mlx, a->win);
		exit(EXIT_SUCCESS);
	}
	if (key == 35)
	{
		if (a->cam.pinhole == 0)
		{
			printf("Scale ortho : %f\n", a->cam.scale);
			a->cam.scale = a->cam.scale * a->cam.p_size;
			printf("Scale persp : %f\n\n", a->cam.scale);
			a->cam.pinhole = 1;
		}
		else
		{
			printf("Scale persp : %f\n", a->cam.scale);
			a->cam.scale = a->cam.scale / a->cam.p_size;
			printf("Scale ortho : %f\n\n", a->cam.scale);
			a->cam.pinhole = 0;
		}
	}
	render(a);
	return (0);
}

int	key_down(int key, t_fdf *a)
{
	if (key == 13)
		a->cam.offset_y += 20;
	if (key == 1)
		a->cam.offset_y -= 20;
	if (key == 0)
		a->cam.offset_x += 20;
	if (key == 2)
		a->cam.offset_x -= 20;
	if (key == 125)
		a->cam.altitude *= 1.0 - 0.1;
	if (key == 126)
		a->cam.altitude *= 1.0 + 0.1;
	render(a);
	return (0);
}
