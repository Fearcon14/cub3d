/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:20:18 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 13:04:14 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_config_section(int fd, int *lines_before_map,
		t_valid_map *vm, t_map *tmap)
{
	char	*line;

	line = get_next_line(fd);
	(*lines_before_map)++;
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (vm->north_textured && vm->south_textured && vm->east_textured
			&& vm->west_textured && vm->floor_colored && vm->ceiling_colored)
		{
			free(line);
			break ;
		}
		c_process_line(line, vm, tmap);
		(*lines_before_map)++;
		free(line);
		line = get_next_line(fd);
	}
}

static int	count_remaining_lines(int fd)
{
	char	*line;
	int		map_lines;

	line = get_next_line(fd);
	map_lines = 1;
	while (line)
	{
		map_lines++;
		free(line);
		line = get_next_line(fd);
	}
	return (map_lines);
}

int	c_count_map_lines(char *filename, int *lines_before_map, t_valid_map *vm,
		t_map *tmap)
{
	int	fd;
	int	map_lines;

	fd = open_map_file(filename);
	process_config_section(fd, lines_before_map, vm, tmap);
	map_lines = count_remaining_lines(fd);
	close(fd);
	return (map_lines);
}

void	c_parse_map(char *filename, t_map *tmap, t_valid_map *vm)
{
	int	lines_before_map;
	int	map_lines;

	lines_before_map = 0;
	map_lines = c_count_map_lines(filename, &lines_before_map, vm, tmap);
	tmap->height = map_lines;
	tmap->map = gc_malloc(sizeof(char *) * (map_lines + 1));
	if (!tmap->map)
		error_exit("Memory allocation failed");
	tmap->map[map_lines] = NULL;
	c_extract_map(filename, tmap, lines_before_map);
}
