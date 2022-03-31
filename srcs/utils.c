/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:14:33 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/31 16:42:43 by amuhleth         ###   ########.fr       */
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

void	die(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
