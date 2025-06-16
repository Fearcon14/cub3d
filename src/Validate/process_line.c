/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:43:33 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/16 12:53:53 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*c_skip_chars(char *line, bool skip_spaces)
{
	if (skip_spaces)
	{
		while (*line && c_isspace(*line))
			line++;
	}
	else
	{
		while (*line && !c_isspace(*line))
			line++;
	}
	return (line);
}

static void	c_assign_texture(const char *dir, char *path, t_valid_map *vm,
		t_map *tmap)
{
	if (ft_strncmp(dir, "NO", 2) == 0)
	{
		tmap->texture.north_path = path;
		vm->north_textured = true;
	}
	else if (ft_strncmp(dir, "SO", 2) == 0)
	{
		tmap->texture.south_path = path;
		vm->south_textured = true;
	}
	else if (ft_strncmp(dir, "EA", 2) == 0)
	{
		tmap->texture.east_path = path;
		vm->east_textured = true;
	}
	else if (ft_strncmp(dir, "WE", 2) == 0)
	{
		tmap->texture.west_path = path;
		vm->west_textured = true;
	}
}

static char	*c_process_texture(char *line, t_valid_map *vm, t_map *tmap,
		const char *dir)
{
	char	*path;

	if (ft_strncmp(line, dir, 2) == 0 && c_isspace(line[2]))
	{
		if ((ft_strncmp(dir, "NO", 2) == 0 && vm->north_textured)
			|| (ft_strncmp(dir, "SO", 2) == 0 && vm->south_textured)
			|| (ft_strncmp(dir, "EA", 2) == 0 && vm->east_textured)
			|| (ft_strncmp(dir, "WE", 2) == 0 && vm->west_textured))
			error_exit("Duplicate texture declaration");
		path = c_extract_path(line + 2);
		c_assign_texture(dir, path, vm, tmap);
		line = c_skip_chars(line + 3, false);
	}
	return (line);
}

static char	*c_process_color(char *line, t_valid_map *vm, t_map *tmap,
		const char *type)
{
	if (ft_strncmp(line, type, 1) == 0 && c_isspace(line[1]))
	{
		if ((ft_strncmp(type, "F", 1) == 0 && vm->floor_colored)
			|| (ft_strncmp(type, "C", 1) == 0 && vm->ceiling_colored))
			error_exit("Duplicate color declaration");
		if (ft_strncmp(type, "F", 1) == 0)
		{
			vm->floor_colored = true;
			tmap->texture.floor_color = c_extract_color(line + 1, vm, true);
		}
		else if (ft_strncmp(type, "C", 1) == 0)
		{
			vm->ceiling_colored = true;
			tmap->texture.ceiling_color = c_extract_color(line + 1, vm, false);
		}
		line = c_skip_chars(line + 2, false);
	}
	return (line);
}

void	c_process_line(char *line, t_valid_map *vm, t_map *tmap)
{
	while (*line)
	{
		line = c_skip_chars(line, true);
		if (!*line)
			return ;
		line = c_process_texture(line, vm, tmap, "NO");
		line = c_process_texture(line, vm, tmap, "SO");
		line = c_process_texture(line, vm, tmap, "EA");
		line = c_process_texture(line, vm, tmap, "WE");
		line = c_process_color(line, vm, tmap, "F");
		line = c_process_color(line, vm, tmap, "C");
		if (*line && !c_isspace(*line))
			error_exit("Invalid identifier in configuration");
	}
}
