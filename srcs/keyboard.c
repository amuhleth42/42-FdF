/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:30:51 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/12 16:02:22 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int key, t_fdf *a)
{
	if (key == 53)
		exit_all(a);
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
	if (key == 8)
		change_color_set(a);
	render(a);
	return (0);
}

int	key_down(int key, t_fdf *a)
{
	if (key == 125)
		a->cam.altitude *= 1.0 - 0.1;
	if (key == 126)
		a->cam.altitude *= 1.0 + 0.1;
	if (key == 49)
	{
		if (a->cam.rot_z == 0)
			a->cam.rot_z = 1;
		else
			a->cam.rot_z = 0;
	}
	render(a);
	return (0);
}
