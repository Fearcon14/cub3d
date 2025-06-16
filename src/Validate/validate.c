/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:13:08 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/16 14:15:05 by ksinn            ###   ########.fr       */
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
	return (c_free_split(rgb), r << 16 | g << 8 | b);
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
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	print_errors(t_valid_map *vm)
{
	if (!vm->legal_chars)
		ft_putstr_fd("Error: Illegal characters in map\n", 2);
	if (!vm->walls_closed)
		ft_putstr_fd("Error: Walls are not closed\n", 2);
	if (!vm->north_path_valid)
		ft_putstr_fd("Error: Invalid north path\n", 2);
	if (!vm->north_textured)
		ft_putstr_fd("Error: North path is not textured\n", 2);
	if (!vm->south_path_valid)
		ft_putstr_fd("Error: Invalid south path\n", 2);
	if (!vm->south_textured)
		ft_putstr_fd("Error: South path is not textured\n", 2);
	if (!vm->east_path_valid)
		ft_putstr_fd("Error: Invalid east path\n", 2);
	if (!vm->east_textured)
		ft_putstr_fd("Error: East path is not textured\n", 2);
	if (!vm->west_path_valid)
		ft_putstr_fd("Error: Invalid west path\n", 2);
	if (!vm->west_textured)
		ft_putstr_fd("Error: West path is not textured\n", 2);
	if (!vm->floor_color_valid)
		ft_putstr_fd("Error: Invalid floor color\n", 2);
	if (!vm->ceiling_color_valid)
		ft_putstr_fd("Error: Invalid ceiling color\n", 2);
	if (vm->player_placed != 1)
	{
		ft_putstr_fd("Error: You have placed ", 2);
		ft_putnbr_fd(vm->player_placed, 2);
		ft_putstr_fd(" players in the map\n", 2);
	}
	if (!vm->legal_chars || !vm->walls_closed || !vm->north_path_valid
		|| !vm->north_textured || !vm->south_path_valid || !vm->south_textured
		|| !vm->east_path_valid || !vm->east_textured || !vm->west_path_valid
		|| !vm->west_textured || !vm->floor_color_valid
		|| !vm->ceiling_color_valid || vm->player_placed != 1)
		return (0);
	return (1);
}

// TODO: maybe have bitmap for error code (1000010) means 2 errors and which ones
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
