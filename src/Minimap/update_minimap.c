/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:36:03 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 14:48:03 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialize minimap background parameters based on player position
 * @param mb The minimap background structure to initialize
 * @param game The game structure
 */
static void	init_minimap_params(t_minimap_background *mb, t_game *game)
{
	mb->center_map_x = game->player.pos.x;
	mb->center_map_y = game->player.pos.y;
	mb->start_map_x = mb->center_map_x - MINIMAP_GRID_SIZE / 2.0;
	mb->start_map_y = mb->center_map_y - MINIMAP_GRID_SIZE / 2.0;
	mb->offset_x = (mb->start_map_x - floor(mb->start_map_x))
		* MINIMAP_CELL_SIZE;
	mb->offset_y = (mb->start_map_y - floor(mb->start_map_y))
		* MINIMAP_CELL_SIZE;
}

/**
 * @brief Determine the color of a cell based on map content
 * @param game The game structure
 * @param map_x The map X coordinate
 * @param map_y The map Y coordinate
 * @return The color to use for this cell
 */
static uint32_t	get_cell_color(t_game *game, int map_x, int map_y)
{
	if (map_x >= 0 && map_y >= 0 && map_y < game->map->height
		&& game->map->map[map_y]
		&& map_x < (int)ft_strlen(game->map->map[map_y])
		&& game->map->map[map_y][map_x] == '2')
	{
		return (MINIMAP_DOOR_COLOR);
	}
	else if (is_wall_at(game, map_x, map_y))
		return (MINIMAP_WALL_COLOR);
	else
		return (MINIMAP_FLOOR_COLOR);
}

/**
 * @brief Render a single cell if it's within bounds
 * @param game The game structure
 * @param mb The minimap background structure
 */
static void	render_cell(t_game *game, t_minimap_background *mb)
{
	if (mb->pixel_x + MINIMAP_CELL_SIZE > 0 && mb->pixel_x < MINIMAP_SIZE - 1
		&& mb->pixel_y + MINIMAP_CELL_SIZE > 0 && mb->pixel_y < MINIMAP_SIZE
		- 1)
	{
		draw_rect(game->minimap_bg, (t_rect){mb->pixel_x, mb->pixel_y,
			MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE}, mb->cell_color);
	}
}

/**
 * @brief Process a single grid cell for minimap rendering
 * @param game The game structure
 * @param mb The minimap background structure
 */
static void	process_grid_cell(t_game *game, t_minimap_background *mb)
{
	mb->map_x = (int)floor(mb->start_map_x) + mb->grid_x;
	mb->map_y = (int)floor(mb->start_map_y) + mb->grid_y;
	mb->pixel_x = 1 + mb->grid_x * MINIMAP_CELL_SIZE - (int)mb->offset_x;
	mb->pixel_y = 1 + mb->grid_y * MINIMAP_CELL_SIZE - (int)mb->offset_y;
	mb->cell_color = get_cell_color(game, mb->map_x, mb->map_y);
	render_cell(game, mb);
}

/**
 * @brief Update the minimap background based on player position
 * @param game The game structure
 */
void	update_minimap_background(t_game *game)
{
	t_minimap_background	mb;

	init_minimap_params(&mb, game);
	fill_image(game->minimap_bg, 0x00000000);
	mb.grid_y = -1;
	while (mb.grid_y <= MINIMAP_GRID_SIZE)
	{
		mb.grid_x = -1;
		while (mb.grid_x <= MINIMAP_GRID_SIZE)
		{
			process_grid_cell(game, &mb);
			mb.grid_x++;
		}
		mb.grid_y++;
	}
	draw_minimap_border(game->minimap_bg);
}
