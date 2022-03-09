/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:12 by amuhleth          #+#    #+#             */
/*   Updated: 2022/03/09 13:40:11 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*read_file(char *path)
{
	t_list	*map;
	char	*line;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		die("open");
	i = 0;
	line = ft_strtrim(get_next_line(fd), "\n");
	if (!line)
		return (NULL);
	map = NULL;
	while (line)
	{
		t_list *tmp;
		tmp = ft_lstnew(line);
		ft_lstadd_back(&map, tmp);
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
	ft_printf("%s\n", map->content);
	while (map->next)
	{
		map = map->next;
		ft_printf("%s\n", map->content);
	}
}

void	parser(char *path, t_fdf *a)
{
	t_list	*map_lines;

	(void) a;
	map_lines = read_file(path);
	print_list(map_lines);
}
