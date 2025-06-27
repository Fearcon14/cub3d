/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:10:34 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:10:38 by ksinn            ###   ########.fr       */
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
	door_tex = mlx_load_png("./assets/textures/Door.png");
	if (!door_tex)
		error_exit(game, "Failed to load door texture");
	game->door_texture = mlx_texture_to_image(game->mlx, door_tex);
	if (!game->door_texture)
		error_exit(game, "Failed to create door image");
	mlx_delete_texture(door_tex);
}
