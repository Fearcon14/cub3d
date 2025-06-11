/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:13:08 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/11 15:45:31 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

char	*c_extract_path(char *line)
{
	char	*path;
	char	*start;
	char	*end;

	while (*line && c_isspace(*line))
		line++;
	if (!*line)
		error_exit("Empty path provided");
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

// TODO: check if we should walk over spaces after extract path
void	c_process_line(char *line, t_valid_map *vm, t_map *tmap)
{
	while (*line)
	{
		while (*line && c_isspace(*line))
			line++;
		if (!*line)
			return ;
		if (ft_strncmp(line, "NO", 2) == 0 && c_isspace(line[2]))
		{
			if (vm->north_textured)
				error_exit("Duplicate North texture declaration");
			tmap->texture.north_path = c_extract_path(line + 2);
			vm->north_textured = true;
			line += 2;
			while (*line && !c_isspace(*line))
				line++;
		}
		else if (ft_strncmp(line, "SO", 2) == 0 && c_isspace(line[2]))
		{
			if (vm->south_textured)
				error_exit("Duplicate South texture declaration");
			tmap->texture.south_path = c_extract_path(line + 2);
			vm->south_textured = true;
			line += 2;
			while (*line && !c_isspace(*line))
				line++;
		}
		else if (ft_strncmp(line, "EA", 2) == 0 && c_isspace(line[2]))
		{
			if (vm->east_textured)
				error_exit("Duplicate East texture declaration");
			tmap->texture.east_path = c_extract_path(line + 2);
			vm->east_textured = true;
			line += 2;
			while (*line && !c_isspace(*line))
				line++;
		}
		else if (ft_strncmp(line, "WE", 2) == 0 && c_isspace(line[2]))
		{
			if (vm->west_textured)
				error_exit("Duplicate West texture declaration");
			tmap->texture.west_path = c_extract_path(line + 2);
			vm->west_textured = true;
			line += 2;
			while (*line && !c_isspace(*line))
				line++;
		}
		else if (ft_strncmp(line, "F", 1) == 0 && c_isspace(line[1]))
		{
			if (vm->floor_colored)
				error_exit("Duplicate Floor color declaration");
			// TODO: Extract floor color
			vm->floor_colored = true;
			line++;
			while (*line && !c_isspace(*line))
				line++;
		}
		else if (ft_strncmp(line, "C", 1) == 0 && c_isspace(line[1]))
		{
			if (vm->ceiling_colored)
				error_exit("Duplicate Ceiling color declaration");
			// TODO: Extract ceiling color
			vm->ceiling_colored = true;
			line++;
			while (*line && !c_isspace(*line))
				line++;
		}
		else if (*line && !c_isspace(*line))
			error_exit("Invalid identifier in configuration");
	}
}

int	c_count_map_lines(char *filename, int *lines_before_map, t_valid_map *vm,
		t_map *tmap)
{
	int		fd;
	int		map_lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("Failed to open file");
	map_lines = 0;
	line = get_next_line(fd);
	lines_before_map++;
	while (line)
	{
		if (line[0] == '\n')
			continue ;
		if (vm->north_textured && !vm->south_textured && !vm->east_textured
			&& !vm->west_textured && !vm->floor_colored && !vm->ceiling_colored)
			break ;
		c_process_line(line, vm, tmap);
		lines_before_map++;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		map_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_lines);
}

char	**c_parse_map(char *filename, t_map *tmap, t_valid_map *vm)
{
	char	**map;
	int		lines_before_map;
	int		map_lines;

	lines_before_map = 0;
	map_lines = c_count_map_lines(filename, &lines_before_map, vm, tmap);
}

// TODO: maybe have bitmap for error code (1000010) means 2 errors and which ones
int	validate_map(char *filename, t_map *tmap)
{
	t_valid_map	vm;

	ft_bzero(&vm, sizeof(t_valid_map));
	vm.legal_chars = true;
	// TODO: Implement map validation logic
	tmap->map = c_parse_map(filename, tmap, &vm);
	vm.legal_chars = c_check_chars(tmap->map);
	(void)filename;
	return (1);
}
