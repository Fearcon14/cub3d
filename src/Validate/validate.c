/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:13:08 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/08 14:06:46 by ksinn            ###   ########.fr       */
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

char	**c_parse_color_string(t_game *game, char *line)
{
	char	**rgb;
	int		i;

	while (*line && c_isspace(*line))
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		error_exit(game, "Memory allocation failed");
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3 || !rgb[0] || !rgb[1] || !rgb[2])
	{
		c_free_split(rgb);
		error_exit(game, "Invalid color format - must be R,G,B");
	}
	return (rgb);
}

void	c_validate_color_values(t_game *game, t_rgba color, char **rgb)
{
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
	{
		c_free_split(rgb);
		error_exit(game, "Invalid color values - must be between 0 and 255");
	}
}

int	c_extract_color(t_game *game, char *line)
{
	t_rgba	color;
	char	**rgb;

	rgb = c_parse_color_string(game, line);
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	color.a = 0xFF;
	c_validate_color_values(game, color, rgb);
	c_free_split(rgb);
	return ((unsigned int)color.r << 24 | (unsigned int)color.g << 16
		| (unsigned int)color.b << 8 | color.a);
}

int	validate_map(char *filename, t_game *game)
{
	c_parse_map(filename, game);
	c_check_chars(game->map->map, game);
	c_check_paths_valid(&game->map->texture, game);
	c_check_walls_closed(game->map->map, game);
	return (1);
}
