/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:12 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/23 13:40:11 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_list	*read_file(char *path)
{
	t_list	*map;
	char	*line;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		die("open failed.\n");
	i = 0;
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

int	check_fdf_format(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (ft_strncmp(path + len - 4, ".fdf", 4) != 0)
		return (0);
	else
		return (1);
}

void	print_list(t_list *map)
{
	printf("%s\n", (char *)map->content);
	while (map->next)
	{
		map = map->next;
		printf("%s\n", (char *)map->content);
	}
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
	int	x;

	x = 0;
	while (line)
	{
		map->world[*i].x = 10 * x;
		map->world[*i].y = 10 * (*i / map->x);
		map->world[*i].z = 1 * ft_atoi(line);
		map->world[*i].color = 0xFFFFFFFF;
		*i += 1;
		while (*line != ' ' && *line != '\0')
			line++;
		while (*line == ' ')
			line++;
		if (*line == '\0')
			break ;
		x++;
	}
}

void	fill_3d_map(t_list *lines, t_map *map)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (lines)
	{
		fill_3d_line(lines->content, map, &i);
		lines = lines->next;
		y++;
	}
}

void	parser(char *path, t_map *map)
{
	t_list	*lines;

	lines = read_file(path);
	print_list(lines);
	map->x = count_elem_in_line(lines->content);
	map->y = ft_lstsize(lines);
	printf("Y : %d\nX : %d\n", map->y, map->x);
	map->size = map->x * map->y;
	map->world = ft_calloc(map->size + 1, sizeof(t_3d));
	map->render = ft_calloc(map->size + 1, sizeof(t_3dv));
	fill_3d_map(lines, map);
}
