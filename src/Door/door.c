/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:10:48 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:18:14 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_door_at(t_game *game, int x, int y)
{
	int	i;

	if (!game->map->doors || game->map->door_count == 0)
		return (0);
	i = 0;
	while (i < game->map->door_count)
	{
		if (game->map->doors[i].x == x && game->map->doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

int	is_door_open(t_game *game, int x, int y)
{
	int	i;

	if (!game->map->doors || game->map->door_count == 0)
		return (0);
	i = 0;
	while (i < game->map->door_count)
	{
		if (game->map->doors[i].x == x && game->map->doors[i].y == y)
			return (game->map->doors[i].is_open);
		i++;
	}
	return (0);
}

static int	is_position_valid_for_door(t_game *game, t_door_data *door_data,
		int *door_x, int *door_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)door_data->current_x;
	map_y = (int)door_data->current_y;
	if (map_x < 0 || map_y < 0 || map_y >= game->map->height)
		return (0);
	if (!game->map->map[map_y]
		|| map_x >= (int)ft_strlen(game->map->map[map_y]))
		return (0);
	if (game->map->map[map_y][map_x] == '1')
		return (0);
	if (game->map->map[map_y][map_x] == '2')
	{
		*door_x = map_x;
		*door_y = map_y;
		return (1);
	}
	return (-1);
}

int	player_facing_door(t_game *game, int *door_x, int *door_y)
{
	t_door_data	door_data;

	door_data.step_size = 0.1;
	door_data.steps = (int)(DOOR_INTERACTION_DISTANCE / door_data.step_size);
	door_data.i = 1;
	while (door_data.i <= door_data.steps)
	{
		door_data.distance = door_data.i * door_data.step_size;
		door_data.current_x = game->player.pos.x + game->player.dir.x
			* door_data.distance;
		door_data.current_y = game->player.pos.y + game->player.dir.y
			* door_data.distance;
		door_data.result = is_position_valid_for_door(game, &door_data, door_x,
				door_y);
		if (door_data.result == 0)
			return (0);
		if (door_data.result == 1)
			return (1);
		door_data.i++;
	}
	return (0);
}

void	door_interact(t_game *game)
{
	int	door_x;
	int	door_y;
	int	i;
	int	player_x;
	int	player_y;

	if (!player_facing_door(game, &door_x, &door_y))
		return ;
	player_x = (int)game->player.pos.x;
	player_y = (int)game->player.pos.y;
	i = 0;
	while (i < game->map->door_count)
	{
		if (game->map->doors[i].x == door_x && game->map->doors[i].y == door_y)
		{
			if (game->map->doors[i].is_open && player_x == door_x
				&& player_y == door_y)
				return ;
			game->map->doors[i].is_open = !game->map->doors[i].is_open;
			return ;
		}
		i++;
	}
}
