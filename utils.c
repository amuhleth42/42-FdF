/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:14:33 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/04 17:16:11 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_img(t_img *i, int x, int y, int color)
{
	char	*dst;

	dst = i->addr + (y * i->ll + x * (i->bpp / 8));
	*(unsigned int*)dst = color;
}

void	die(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
