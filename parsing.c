/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:12 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/04 20:44:38 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**read_file(char *path)
{
	char	**map;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		die("open");
	map = ft_calloc(MAX_LINE, sizeof(char *));
	if (!map)
		die("calloc");
	i = 0;
	map[i] = ft_strtrim(get_next_line(fd), "\n");
	while (map[i] != NULL && i < MAX_LINE)
	{
		i++;
		map[i] = ft_strtrim(get_next_line(fd), "\n");
	}
	close(fd);
	return (map);
}

int	check_fdf_format(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (fd_strncmp(path + len - 4, ".fdf", 4) != 0)
		return (0);
	else
		return (1);
}

void	parser(char *path, t_fdf *a)
{
	char	**lines;

	lines = read_file(path);
}
