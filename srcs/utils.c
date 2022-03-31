/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:14:33 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 15:17:49 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	switch_bool(int *b)
{
	if (*b == 0)
		*b = 1;
	else
		*b = 0;
}

void	put_pixel_to_img(t_img *i, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < WIN_WIDTH && 0 <= y && y < WIN_HEIGHT)
	{
		dst = i->addr + (y * i->ll + x * (i->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	die(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
