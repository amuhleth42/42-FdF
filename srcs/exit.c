/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:13:38 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/12 16:03:39 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	die(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_maps(t_fdf *a)
{
	if (a->map.world)
		free(a->map.world);
	if (a->map.render)
		free(a->map.render);
	if (a->map.map_2d)
		free(a->map.map_2d);
}

void	exit_all(t_fdf *a)
{
	free_maps(a);
	mlx_destroy_image(a->mlx, a->i.img);
	mlx_destroy_window(a->mlx, a->win);
	exit(EXIT_SUCCESS);
}

int	red_cross(t_fdf *a)
{
	exit_all(a);
	return (0);
}
