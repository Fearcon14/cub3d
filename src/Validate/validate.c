/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:13:08 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/23 13:06:16 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*c_extract_path(char *line)
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
		error_exit("Memory allocation failed");
	gc_add_context(VALIDATION, path);
	return (path);
}

int	c_extract_color(char *line, t_valid_map *vm, bool is_floor)
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
		error_exit("Memory allocation failed");
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

void	c_extract_map(char *filename, t_map *tmap, int lines_before_map)
{
	int		fd;
	int		i;
	char	*line;

	fd = open_map_file(filename);
	i = 0;
	while (i++ < lines_before_map)
	{
		line = get_next_line(fd);
		free(line);
	}
	line = get_next_line(fd);
	while (*line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		tmap->map[i++] = ft_strtrim(line, "\n");
		if (tmap->map[i - 1])
			gc_add_context(MAP, tmap->map[i - 1]);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	validate_map(char *filename, t_map *tmap)
{
	t_valid_map	vm;

	ft_bzero(&vm, sizeof(t_valid_map));
	vm.legal_chars = true;
	c_parse_map(filename, tmap, &vm);
	c_check_chars(tmap->map, &vm);
	c_check_paths_valid(&tmap->texture, &vm);
	c_check_walls_closed(tmap->map, &vm);
	return (print_errors(&vm));
}
