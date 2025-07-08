/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:43:33 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/08 14:00:17 by ksinn            ###   ########.fr       */
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

static void	c_assign_texture(const char *dir, char *path, t_game *game)
{
	if (ft_strncmp(dir, "NO", 2) == 0)
		game->map->texture.north_path = path;
	else if (ft_strncmp(dir, "SO", 2) == 0)
		game->map->texture.south_path = path;
	else if (ft_strncmp(dir, "EA", 2) == 0)
		game->map->texture.east_path = path;
	else if (ft_strncmp(dir, "WE", 2) == 0)
		game->map->texture.west_path = path;
}

static char	*c_process_texture(char *line, t_game *game, const char *dir)
{
	char	*path;

	if (ft_strncmp(line, dir, 2) == 0 && c_isspace(line[2]))
	{
		if ((ft_strncmp(dir, "NO", 2) == 0 && game->map->texture.north_path)
			|| (ft_strncmp(dir, "SO", 2) == 0 && game->map->texture.south_path)
			|| (ft_strncmp(dir, "EA", 2) == 0 && game->map->texture.east_path)
			|| (ft_strncmp(dir, "WE", 2) == 0 && game->map->texture.west_path))
		{
			error_exit(game, "Duplicate texture declaration");
		}
		path = c_extract_path(game, line + 2);
		c_assign_texture(dir, path, game);
		line = c_skip_chars(line + 3, false);
	}
	return (line);
}

static char	*c_process_color(char *line, t_game *game, const char *type)
{
	if (ft_strncmp(line, type, 1) == 0 && c_isspace(line[1]))
	{
		if ((ft_strncmp(type, "F", 1) == 0
				&& game->map->texture.floor_color_set) || (ft_strncmp(type, "C",
					1) == 0 && game->map->texture.ceiling_color_set))
		{
			error_exit(game, "Duplicate color declaration");
		}
		if (ft_strncmp(type, "F", 1) == 0)
		{
			game->map->texture.floor_color = c_extract_color(game, line + 1);
			game->map->texture.floor_color_set = true;
		}
		else if (ft_strncmp(type, "C", 1) == 0)
		{
			game->map->texture.ceiling_color = c_extract_color(game, line + 1);
			game->map->texture.ceiling_color_set = true;
		}
		line = c_skip_chars(line + 2, false);
	}
	return (line);
}

void	c_process_line(char *line, t_game *game)
{
	while (*line)
	{
		line = c_skip_chars(line, true);
		if (!*line)
			return ;
		line = c_process_texture(line, game, "NO");
		line = c_process_texture(line, game, "SO");
		line = c_process_texture(line, game, "EA");
		line = c_process_texture(line, game, "WE");
		line = c_process_color(line, game, "F");
		line = c_process_color(line, game, "C");
		if (*line && !c_isspace(*line))
		{
			error_exit(game, "Illegal / missing identifier in configuration");
		}
	}
}
