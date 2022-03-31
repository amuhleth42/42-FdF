/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:30:51 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 16:16:21 by amuhleth         ###   ########.fr       */
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
	if (key == 35)
	{
		if (a->cam.pinhole == 0)
		{
			a->cam.scale = a->cam.scale * a->cam.p_size;
			a->cam.pinhole = 1;
		}
		else
		{
			a->cam.scale = a->cam.scale / a->cam.p_size;
			a->cam.pinhole = 0;
		}
	}
	render(a);
	return (0);
}

int	key_down(int key, t_fdf *a)
{
	if (key == 125)
		a->cam.altitude *= 1.0 - 0.1;
	if (key == 126)
		a->cam.altitude *= 1.0 + 0.1;
	if (key == 0)
		switch_bool(&a->cam.rot_z);
	render(a);
	return (0);
}
