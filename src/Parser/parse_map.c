/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:20:18 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/08 14:01:13 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_config_section(int fd, int *lines_before_map, t_game *game)
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
		if (game->map->texture.north_path && game->map->texture.south_path
			&& game->map->texture.east_path && game->map->texture.west_path
			&& game->map->texture.floor_color_set
			&& game->map->texture.ceiling_color_set)
		{
			free(line);
			break ;
		}
		c_process_line(line, game);
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

int	c_count_map_lines(char *filename, int *lines_before_map, t_game *game)
{
	int	fd;
	int	map_lines;

	fd = open_map_file(game, filename);
	process_config_section(fd, lines_before_map, game);
	map_lines = count_remaining_lines(fd);
	get_next_line(-1);
	close(fd);
	return (map_lines);
}

void	c_parse_map(char *filename, t_game *game)
{
	int	lines_before_map;
	int	map_lines;

	game->map = gc_malloc(sizeof(t_map));
	if (!game->map)
		error_exit(game, "Map allocation failed");
	gc_add_context(MAP, game->map);
	ft_bzero(&game->map->texture, sizeof(t_texture));
	lines_before_map = 0;
	map_lines = c_count_map_lines(filename, &lines_before_map, game);
	game->map->height = map_lines;
	game->map->map = gc_malloc(sizeof(char *) * (map_lines + 1));
	if (!game->map->map)
		error_exit(game, "Map allocation failed");
	gc_add_context(MAP, game->map->map);
	game->map->map[map_lines] = NULL;
	c_extract_map(filename, game, lines_before_map);
}
