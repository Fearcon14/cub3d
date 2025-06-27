/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:29:44 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:40:10 by ksinn            ###   ########.fr       */
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

static void	calculate_closest_point_and_distance(t_wall_collision *wc, double x,
		double y)
{
	wc->closest_x = fmax(wc->map_x, fmin(x, wc->map_x + 1.0));
	wc->closest_y = fmax(wc->map_y, fmin(y, wc->map_y + 1.0));
	wc->distance = sqrt((x - wc->closest_x) * (x - wc->closest_x) + (y
				- wc->closest_y) * (y - wc->closest_y));
}

static int	check_wall_collision(t_wall_collision *wc, double x, double y)
{
	calculate_closest_point_and_distance(wc, x, y);
	if (wc->distance < PLAYER_OFFSET)
		return (1);
	return (0);
}

static int	check_door_collision(t_game *game, t_wall_collision *wc, double x,
		double y)
{
	if (!is_door_open(game, wc->map_x, wc->map_y))
	{
		calculate_closest_point_and_distance(wc, x, y);
		if (wc->distance < PLAYER_OFFSET)
			return (1);
	}
	return (0);
}

int	is_wall_collision(t_game *game, double x, double y)
{
	t_wall_collision	wc;

	setup_collision_bounds(&wc, x, y);
	wc.map_y = wc.min_y;
	while (wc.map_y <= wc.max_y)
	{
		wc.map_x = wc.min_x - 1;
		while (++wc.map_x <= wc.max_x)
		{
			if (!is_valid_position(game, wc.map_x, wc.map_y))
				return (1);
			if (game->map->map[wc.map_y][wc.map_x] == '1')
			{
				if (check_wall_collision(&wc, x, y))
					return (1);
			}
			if (game->map->map[wc.map_y][wc.map_x] == '2')
			{
				if (check_door_collision(game, &wc, x, y))
					return (1);
			}
		}
		wc.map_y++;
	}
	return (0);
}
