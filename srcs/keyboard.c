/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:30:51 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 17:09:33 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int key, t_fdf *a)
{
	ft_printf("%d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(a->mlx, a->win);
		exit(EXIT_SUCCESS);
	}
	if (key == 35)
	{
		if (a->cam.pinhole == 0)
			a->cam.pinhole = 1;
		else
			a->cam.pinhole = 0;
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
	render(a);
	return (0);
}
