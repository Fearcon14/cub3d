/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:13:08 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/08 13:51:37 by ksinn            ###   ########.fr       */
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

int	c_extract_color(t_game *game, char *line)
{
	int		r;
	int		g;
	int		b;
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
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		c_free_split(rgb);
		error_exit(game, "Invalid color values - must be between 0 and 255");
	}
	return (c_free_split(rgb),
		(unsigned int)r << 24 | (unsigned int)g << 16 | (unsigned int)b << 8 | 0xFF);
}

int	validate_map(char *filename, t_game *game)
{
	c_parse_map(filename, game);
	c_check_chars(game->map->map, game);
	c_check_paths_valid(&game->map->texture, game);
	c_check_walls_closed(game->map->map, game);
	return (1);
}
