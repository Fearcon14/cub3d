/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:29:44 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 15:26:04 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_position(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_y >= game->map->height)
		return (0);
	if (!game->map->map[map_y]
		|| map_x >= (int)ft_strlen(game->map->map[map_y]))
		return (0);
	return (1);
}

int	is_wall_collision(t_game *game, double x, double y)
{
	double	distance;
	int		min_x, max_x, min_y, max_y;
	int		map_x, map_y;
	double	closest_x, closest_y;

	min_x = (int)floor(x - PLAYER_OFFSET);
	max_x = (int)floor(x + PLAYER_OFFSET);
	min_y = (int)floor(y - PLAYER_OFFSET);
	max_y = (int)floor(y + PLAYER_OFFSET);
	for (map_y = min_y; map_y <= max_y; map_y++)
	{
		for (map_x = min_x; map_x <= max_x; map_x++)
		{
			if (!is_valid_position(game, map_x, map_y))
				return (1);
			if (game->map->map[map_y][map_x] == '1')
			{
				closest_x = fmax(map_x, fmin(x, map_x + 1.0));
				closest_y = fmax(map_y, fmin(y, map_y + 1.0));
				distance = sqrt((x - closest_x) * (x - closest_x) + (y
							- closest_y) * (y - closest_y));
				if (distance < PLAYER_OFFSET)
					return (1);
			}
		}
	}
	return (0);
}
