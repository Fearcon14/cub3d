/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:13:08 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/27 14:08:57 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*c_extract_path(t_game *game, char *line)
{
	char	*path;
	char	*start;
	char	*end;

	while (*line && c_isspace(*line))
		line++;
	if (!*line)
		return (ft_putstr_fd("Error: Empty path provided\n", 2), NULL);
	start = line;
	while (*line && !c_isspace(*line))
		line++;
	end = line;
	path = ft_substr(start, 0, end - start);
	if (!path)
		error_exit(game, "Memory allocation failed");
	gc_add_context(VALIDATION, path);
	return (path);
}

int	c_extract_color(t_game *game, char *line, t_valid_map *vm, bool is_floor)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	if (is_floor)
		vm->floor_color_valid = true;
	else
		vm->ceiling_color_valid = true;
	while (*line && c_isspace(*line))
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		error_exit(game, "Memory allocation failed");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		if (is_floor)
			vm->floor_color_valid = false;
		else
			vm->ceiling_color_valid = false;
	}
	return (c_free_split(rgb), r << 24 | g << 16 | b << 8 | 0xFF);
}

void	c_extract_map(char *filename, t_game *game, int lines_before_map)
{
	t_extract_map	em;

	em.fd = open_map_file(game, filename);
	em.i = 0;
	while (em.i++ < lines_before_map)
	{
		em.line = get_next_line(em.fd);
		free(em.line);
	}
	em.line = get_next_line(em.fd);
	while (*em.line && *em.line == '\n')
	{
		free(em.line);
		em.line = get_next_line(em.fd);
	}
	em.i = 0;
	while (em.line)
	{
		game->map->map[em.i++] = ft_strtrim(em.line, "\n");
		if (game->map->map[em.i - 1])
			gc_add_context(MAP, game->map->map[em.i - 1]);
		free(em.line);
		em.line = get_next_line(em.fd);
	}
	close(em.fd);
}

int	validate_map(char *filename, t_game *game)
{
	t_valid_map	vm;

	ft_bzero(&vm, sizeof(t_valid_map));
	vm.legal_chars = true;
	c_parse_map(filename, game, &vm);
	c_check_chars(game->map->map, &vm);
	c_check_paths_valid(&game->map->texture, &vm);
	c_check_walls_closed(game->map->map, &vm);
	return (print_errors(&vm));
}
