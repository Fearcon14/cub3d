/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:20:18 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/07 18:02:43 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_config_section(int fd, int *lines_before_map,
		t_valid_map *vm, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			(*lines_before_map)++;
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
		c_process_line(line, vm, game);
		(*lines_before_map)++;
		free(line);
		line = get_next_line(fd);
	}
}

static int	count_remaining_lines(int fd)
{
	char	*line;
	int		map_lines;

	map_lines = 1;
	line = get_next_line(fd);
	while (line)
	{
		map_lines++;
		free(line);
		line = get_next_line(fd);
	}
	return (map_lines);
}

int	c_count_map_lines(char *filename, int *lines_before_map, t_valid_map *vm,
		t_game *game)
{
	int	fd;
	int	map_lines;

	fd = open_map_file(game, filename);
	process_config_section(fd, lines_before_map, vm, game);
	map_lines = count_remaining_lines(fd);
	close(fd);
	return (map_lines);
}

void	c_parse_map(char *filename, t_game *game, t_valid_map *vm)
{
	int	lines_before_map;
	int	map_lines;

	game->map = gc_malloc(sizeof(t_map));
	if (!game->map)
	{
		vm->map_allocated = false;
		return ;
	}
	gc_add_context(MAP, game->map);
	lines_before_map = 0;
	map_lines = c_count_map_lines(filename, &lines_before_map, vm, game);
	game->map->height = map_lines;
	game->map->map = gc_malloc(sizeof(char *) * (map_lines + 1));
	if (!game->map->map)
	{
		vm->map_allocated = false;
		return ;
	}
	gc_add_context(MAP, game->map->map);
	game->map->map[map_lines] = NULL;
	c_extract_map(filename, game, lines_before_map, vm);
	vm->map_allocated = true;
}
