/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:12 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/08 18:01:52 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*read_file(char *path)
{
	t_list	*map;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		die("open : an error occured when opening file.");
	line = ft_strtrim(get_next_line(fd), "\n");
	if (!line)
		return (NULL);
	map = NULL;
	while (line)
	{
		ft_lstadd_back(&map, ft_lstnew(line));
		line = ft_strtrim(get_next_line(fd), "\n");
	}
	close(fd);
	return (map);
}

int	count_elem_in_line(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		while (s[i] != ' ' && s[i])
			i++;
		count++;
	}
	if (s[i - 1] == ' ')
		count--;
	return (count);
}

void	fill_3d_line(char *line, t_map *map, int *i)
{
	int		x;
	char	**points;

	x = 0;
	points = ft_split(line, ' ');
	while (x < map->x)
	{
		map->world[*i].x = 10 * x - 10 * map->x / 2;
		map->world[*i].y = 10 * (*i / map->x) - 10 * map->y / 2;
		map->world[*i].z = ft_atoi(points[x]);
		if (map->world[*i].z < map->z_min)
			map->z_min = map->world[*i].z;
		if (map->world[*i].z > map->z_max)
			map->z_max = map->world[*i].z;
		*i += 1;
		x++;
	}
	free(points);
}

void	fill_3d_map(t_list *lines, t_map *map)
{
	int	i;
	int	y;

	map->z_max = 0;
	map->z_min = 0;
	i = 0;
	y = 0;
	while (lines)
	{
		fill_3d_line(lines->content, map, &i);
		lines = lines->next;
		y++;
	}
}

void	parser(char *path, t_map *map, t_fdf *a)
{
	t_list	*lines;

	lines = read_file(path);
	if (!lines)
		die("parsing : empty file");
	map->x = count_elem_in_line(lines->content);
	map->y = ft_lstsize(lines);
	ft_printf("Y : %d\nX : %d\n", map->y, map->x);
	map->size = map->x * map->y;
	map->world = ft_calloc(map->size + 1, sizeof(t_3d));
	map->render = ft_calloc(map->size + 1, sizeof(t_3dv));
	map->map_2d = ft_calloc(map->size + 1, sizeof(t_2d));
	if (!map->world || !map->render || !map->map_2d)
	{
		free_maps(a);
		die("malloc error");
	}
	fill_3d_map(lines, map);
	color_map(map);
}
