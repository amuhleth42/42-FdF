/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:16:20 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/01 14:43:49 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_line.h"

int	key_hook(int key, t_game *a)
{
	if (key == 53)
	{
		mlx_destroy_window(a->mlx, a->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_game *a)
{
	(void) x;
	(void) y;
	(void) a;
	ft_printf("%d\n", button);
	ft_printf("X: %d, Y: %d\n", x, y);
	return (0);
}

int	main(void)
{
	t_game a;

	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, 1000, 1000, "Draw_line");
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_mouse_hook(a.win, &mouse_hook, &a);
	mlx_loop(a.mlx);
}
