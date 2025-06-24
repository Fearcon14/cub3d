/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:10:48 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 12:45:14 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_doors(t_game *game)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->map[y] && game->map->map[y][x])
		{
			if (game->map->map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	populate_doors(t_game *game)
{
	int	door_index;
	int	y;
	int	x;

	door_index = 0;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->map[y] && game->map->map[y][x])
		{
			if (game->map->map[y][x] == '2')
			{
				game->map->doors[door_index].x = x;
				game->map->doors[door_index].y = y;
				game->map->doors[door_index].is_open = false;
				door_index++;
			}
			x++;
		}
		y++;
	}
}

void	door_init(t_game *game)
{
	mlx_texture_t	*door_tex;

	game->map->door_count = count_doors(game);
	if (game->map->door_count == 0)
	{
		game->map->doors = NULL;
		game->door_texture = NULL;
		return ;
	}
	game->map->doors = gc_malloc(sizeof(t_door) * game->map->door_count);
	if (!game->map->doors)
		error_exit(game, "Failed to allocate memory for doors");
	gc_add_context(MAP, game->map->doors);
	populate_doors(game);
	door_tex = mlx_load_png("./assets/textures/E_door1_1.png");
	if (!door_tex)
		error_exit(game, "Failed to load door texture");
	game->door_texture = mlx_texture_to_image(game->mlx, door_tex);
	if (!game->door_texture)
		error_exit(game, "Failed to create door image");
	mlx_delete_texture(door_tex);
}

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

int	player_facing_door(t_game *game, int *door_x, int *door_y)
{
	double	step_size;
	double	current_x;
	double	current_y;
	double	distance;
	int		map_x;
	int		map_y;
	int		steps;
	int		i;

	step_size = 0.1; // Check every 0.1 units
	steps = (int)(DOOR_INTERACTION_DISTANCE / step_size);
	i = 1; // Start from step 1 to avoid checking player's current position
	while (i <= steps)
	{
		distance = i * step_size;
		current_x = game->player.pos.x + game->player.dir.x * distance;
		current_y = game->player.pos.y + game->player.dir.y * distance;
		map_x = (int)current_x;
		map_y = (int)current_y;
		// Check bounds
		if (map_x < 0 || map_y < 0 || map_y >= game->map->height)
			return (0);
		if (!game->map->map[map_y]
			|| map_x >= (int)ft_strlen(game->map->map[map_y]))
			return (0);
		// If we hit a wall, stop looking
		if (game->map->map[map_y][map_x] == '1')
			return (0);
		// If we hit a door, we found one!
		if (game->map->map[map_y][map_x] == '2')
		{
			*door_x = map_x;
			*door_y = map_y;
			return (1);
		}
		i++;
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
	// Get player's current grid position
	player_x = (int)game->player.pos.x;
	player_y = (int)game->player.pos.y;
	i = 0;
	while (i < game->map->door_count)
	{
		if (game->map->doors[i].x == door_x && game->map->doors[i].y == door_y)
		{
			// If door is open and player is standing inside it, prevent closing
			if (game->map->doors[i].is_open && player_x == door_x
				&& player_y == door_y)
				return ; // Cannot close door while standing in it
			game->map->doors[i].is_open = !game->map->doors[i].is_open;
			return ;
		}
		i++;
	}
}
