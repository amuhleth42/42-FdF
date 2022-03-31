/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:13:38 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 17:23:20 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
