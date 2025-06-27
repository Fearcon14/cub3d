/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:43:33 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 15:26:32 by ksinn            ###   ########.fr       */
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
		t_game *game)
{
	if (ft_strncmp(dir, "NO", 2) == 0)
	{
		game->map->texture.north_path = path;
		vm->north_textured = true;
	}
	else if (ft_strncmp(dir, "SO", 2) == 0)
	{
		game->map->texture.south_path = path;
		vm->south_textured = true;
	}
	else if (ft_strncmp(dir, "EA", 2) == 0)
	{
		game->map->texture.east_path = path;
		vm->east_textured = true;
	}
	else if (ft_strncmp(dir, "WE", 2) == 0)
	{
		game->map->texture.west_path = path;
		vm->west_textured = true;
	}
}

static char	*c_process_texture(char *line, t_valid_map *vm, t_game *game,
		const char *dir)
{
	char	*path;

	if (ft_strncmp(line, dir, 2) == 0 && c_isspace(line[2]))
	{
		if ((ft_strncmp(dir, "NO", 2) == 0 && vm->north_textured)
			|| (ft_strncmp(dir, "SO", 2) == 0 && vm->south_textured)
			|| (ft_strncmp(dir, "EA", 2) == 0 && vm->east_textured)
			|| (ft_strncmp(dir, "WE", 2) == 0 && vm->west_textured))
		{
			ft_putstr_fd("Duplicate texture declaration\n", 2);
			vm->north_textured = false;
			vm->south_textured = false;
			vm->east_textured = false;
			vm->west_textured = false;
		}
		path = c_extract_path(game, line + 2);
		c_assign_texture(dir, path, vm, game);
		line = c_skip_chars(line + 3, false);
	}
	return (line);
}

static char	*c_process_color(char *line, t_valid_map *vm, t_game *game,
		const char *type)
{
	if (ft_strncmp(line, type, 1) == 0 && c_isspace(line[1]))
	{
		if ((ft_strncmp(type, "F", 1) == 0 && vm->floor_colored)
			|| (ft_strncmp(type, "C", 1) == 0 && vm->ceiling_colored))
		{
			ft_putstr_fd("Duplicate color declaration\n", 2);
			vm->floor_colored = false;
			vm->ceiling_colored = false;
		}
		if (ft_strncmp(type, "F", 1) == 0)
		{
			vm->floor_colored = true;
			game->map->texture.floor_color = c_extract_color(game, line + 1, vm,
					true);
		}
		else if (ft_strncmp(type, "C", 1) == 0)
		{
			vm->ceiling_colored = true;
			game->map->texture.ceiling_color = c_extract_color(game, line + 1,
					vm, false);
		}
		line = c_skip_chars(line + 2, false);
	}
	return (line);
}

void	c_process_line(char *line, t_valid_map *vm, t_game *game)
{
	while (*line)
	{
		line = c_skip_chars(line, true);
		if (!*line)
			return ;
		line = c_process_texture(line, vm, game, "NO");
		line = c_process_texture(line, vm, game, "SO");
		line = c_process_texture(line, vm, game, "EA");
		line = c_process_texture(line, vm, game, "WE");
		line = c_process_color(line, vm, game, "F");
		line = c_process_color(line, vm, game, "C");
		if (*line && !c_isspace(*line))
		{
			vm->north_textured = false;
			vm->south_textured = false;
			vm->east_textured = false;
			vm->west_textured = false;
			vm->illegal_identifier = true;
			break ;
		}
	}
}
