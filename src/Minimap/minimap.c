/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:32:53 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 12:58:15 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if a map coordinate is a wall or out of bounds
 * @param game The game structure
 * @param map_x X coordinate in map grid
 * @param map_y Y coordinate in map grid
 * @return 1 if wall/out of bounds, 0 if empty space
 */
static int	is_wall_at(t_game *game, int map_x, int map_y)
{
	char	cell;

	if (map_y < 0 || map_y >= game->map->height)
		return (1);
	if (map_x < 0 || !game->map->map[map_y]
		|| map_x >= (int)ft_strlen(game->map->map[map_y]))
		return (1);
	cell = game->map->map[map_y][map_x];
	/* Return 1 (wall) for: walls ('1'), spaces (' '),
		and any other non-floor character */
	/* Return 0 (floor) only for: floor ('0'), and player start positions ('N',
		'S', 'E', 'W') */
	if (cell == '2')
	{
		// For doors, check if they're open or closed
		return (!is_door_open(game, map_x, map_y));
	}
	return (cell != '0' && cell != 'N' && cell != 'S' && cell != 'E'
		&& cell != 'W');
}

/**

	* @brief Check if a point is visible from the player position (simple line-of-sight check)
 * @param game The game structure
 * @param target_x Target X coordinate in map space
 * @param target_y Target Y coordinate in map space
 * @return 1 if visible, 0 if blocked by wall
 */
static int	is_point_visible(t_game *game, double target_x, double target_y)
{
	double	dx;
	double	dy;
	double	distance;
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	int		steps;
	int		i;

	dx = target_x - game->player.pos.x;
	dy = target_y - game->player.pos.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > MINIMAP_VISION_RANGE)
		return (0);
	steps = (int)(distance * 10); // Check every 0.1 units
	if (steps <= 0)
		return (1);
	step_x = dx / steps;
	step_y = dy / steps;
	current_x = game->player.pos.x;
	current_y = game->player.pos.y;
	i = 0;
	while (i < steps)
	{
		current_x += step_x;
		current_y += step_y;
		if (is_wall_at(game, (int)current_x, (int)current_y))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Check if a point is within the player's field of view cone
 * @param game The game structure
 * @param target_x Target X coordinate in map space
 * @param target_y Target Y coordinate in map space
 * @return 1 if within FOV, 0 if outside
 */
static int	is_in_fov(t_game *game, double target_x, double target_y)
{
	double	dx;
	double	dy;
	double	target_angle;
	double	player_angle;
	double	angle_diff;
	double	half_fov_rad;

	dx = target_x - game->player.pos.x;
	dy = target_y - game->player.pos.y;
	// Calculate angle to target
	target_angle = atan2(dy, dx);
	// Calculate player's facing angle
	player_angle = atan2(game->player.dir.y, game->player.dir.x);
	// Calculate angle difference
	angle_diff = target_angle - player_angle;
	// Normalize angle difference to [-PI, PI]
	while (angle_diff > PI)
		angle_diff -= TWO_PI;
	while (angle_diff < -PI)
		angle_diff += TWO_PI;
	// Check if within FOV
	half_fov_rad = (FOV * PI / 180.0) / 2.0;
	return (fabs(angle_diff) <= half_fov_rad);
}

/**
 * @brief Draw the vision cone overlay
 * @param game The game structure
 */
static void	draw_vision_cone(t_game *game)
{
	int		pixel_x;
	int		pixel_y;
	double	map_x;
	double	map_y;
	double	center_map_x;
	double	center_map_y;
	double	start_map_x;
	double	start_map_y;

	center_map_x = game->player.pos.x;
	center_map_y = game->player.pos.y;
	start_map_x = center_map_x - MINIMAP_GRID_SIZE / 2.0;
	start_map_y = center_map_y - MINIMAP_GRID_SIZE / 2.0;
	pixel_y = 1;
	while (pixel_y < MINIMAP_SIZE - 1)
	{
		pixel_x = 1;
		while (pixel_x < MINIMAP_SIZE - 1)
		{
			// Convert pixel coordinates back to map coordinates
			map_x = start_map_x + (double)(pixel_x - 1) / MINIMAP_CELL_SIZE;
			map_y = start_map_y + (double)(pixel_y - 1) / MINIMAP_CELL_SIZE;
			// Check if this point is within FOV and visible
			if (is_in_fov(game, map_x, map_y) && is_point_visible(game, map_x,
					map_y))
			{
				// Apply vision cone overlay (blend with existing pixel)
				mlx_put_pixel(game->minimap_player, pixel_x, pixel_y,
					MINIMAP_VISION_COLOR);
			}
			pixel_x++;
		}
		pixel_y++;
	}
}

/**
 * @brief Fill an entire image with a specific color
 * @param img The image to fill
 * @param color The color to fill with
 */
static void	fill_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draw a filled rectangle on an image
 * @param img The image to draw on
 * @param start_x Starting X pixel coordinate
 * @param start_y Starting Y pixel coordinate
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color Color to draw
 */
static void	draw_rect(mlx_image_t *img, int start_x, int start_y, int width,
		int height, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (start_x + x >= 0 && start_x + x < (int)img->width && start_y
				+ y >= 0 && start_y + y < (int)img->height)
			{
				mlx_put_pixel(img, start_x + x, start_y + y, color);
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief Draw the minimap border on the background image
 * @param img The minimap background image
 */
static void	draw_minimap_border(mlx_image_t *img)
{
	uint32_t	i;

	// Top and bottom borders
	i = 0;
	while (i < img->width)
	{
		mlx_put_pixel(img, i, 0, MINIMAP_BORDER_COLOR);
		mlx_put_pixel(img, i, img->height - 1, MINIMAP_BORDER_COLOR);
		i++;
	}
	// Left and right borders
	i = 0;
	while (i < img->height)
	{
		mlx_put_pixel(img, 0, i, MINIMAP_BORDER_COLOR);
		mlx_put_pixel(img, img->width - 1, i, MINIMAP_BORDER_COLOR);
		i++;
	}
}

/**
 * @brief Update the minimap background based on player position
 * @param game The game structure
 */
static void	update_minimap_background(t_game *game)
{
	int			grid_x;
	int			grid_y;
	int			map_x;
	int			map_y;
	int			pixel_x;
	int			pixel_y;
	uint32_t	cell_color;
	double		center_map_x;
	double		center_map_y;
	double		start_map_x;
	double		start_map_y;
	double		offset_x;
	double		offset_y;

	// Calculate the center of the visible map area (using exact player position)
	center_map_x = game->player.pos.x;
	center_map_y = game->player.pos.y;
	start_map_x = center_map_x - MINIMAP_GRID_SIZE / 2.0;
	start_map_y = center_map_y - MINIMAP_GRID_SIZE / 2.0;
	// Calculate pixel offset for smooth scrolling
	offset_x = (start_map_x - floor(start_map_x)) * MINIMAP_CELL_SIZE;
	offset_y = (start_map_y - floor(start_map_y)) * MINIMAP_CELL_SIZE;
	// Clear the background image
	fill_image(game->minimap_bg, 0x00000000); // Transparent
	// Draw minimap grid (we need to draw one extra cell in each direction for smooth scrolling)
	grid_y = -1;
	while (grid_y <= MINIMAP_GRID_SIZE)
	{
		grid_x = -1;
		while (grid_x <= MINIMAP_GRID_SIZE)
		{
			// Calculate actual map coordinates
			map_x = (int)floor(start_map_x) + grid_x;
			map_y = (int)floor(start_map_y) + grid_y;
			// Calculate pixel position in minimap (with 1 pixel border and smooth offset)
			pixel_x = 1 + grid_x * MINIMAP_CELL_SIZE - (int)offset_x;
			pixel_y = 1 + grid_y * MINIMAP_CELL_SIZE - (int)offset_y;
			// Choose color based on map content
			if (map_x >= 0 && map_y >= 0 && map_y < game->map->height
				&& game->map->map[map_y]
				&& map_x < (int)ft_strlen(game->map->map[map_y])
				&& game->map->map[map_y][map_x] == '2')
			{
				// This is a door - use door color
				cell_color = MINIMAP_DOOR_COLOR;
			}
			else if (is_wall_at(game, map_x, map_y))
				cell_color = MINIMAP_WALL_COLOR;
			else
				cell_color = MINIMAP_FLOOR_COLOR;
			// Draw the cell only if it's visible within the minimap bounds
			if (pixel_x + MINIMAP_CELL_SIZE > 0 && pixel_x < MINIMAP_SIZE - 1
				&& pixel_y + MINIMAP_CELL_SIZE > 0 && pixel_y < MINIMAP_SIZE
				- 1)
			{
				draw_rect(game->minimap_bg, pixel_x, pixel_y, MINIMAP_CELL_SIZE,
					MINIMAP_CELL_SIZE, cell_color);
			}
			grid_x++;
		}
		grid_y++;
	}
	// Draw border around minimap
	draw_minimap_border(game->minimap_bg);
}

/**
 * @brief Update the player indicator position and direction
 * @param game The game structure
 */
static void	update_minimap_player(t_game *game)
{
	int	player_pixel_x;
	int	player_pixel_y;

	// Clear the player image
	fill_image(game->minimap_player, 0x00000000); // Transparent
	// Draw vision cone first (so it appears behind the player)
	draw_vision_cone(game);
	// Player is always at the center of the minimap
	player_pixel_x = MINIMAP_SIZE / 2;
	player_pixel_y = MINIMAP_SIZE / 2;
	// Draw player dot (3x3 red square)
	draw_rect(game->minimap_player, player_pixel_x - 1, player_pixel_y - 1, 3,
		3, MINIMAP_PLAYER_COLOR);
}

/**
 * @brief Initialize minimap images and position them
 * @param game The game structure
 * @return 1 on success, 0 on failure
 */
int	init_minimap(t_game *game)
{
	int	minimap_x;
	int	minimap_y;

	// Position minimap in top-right corner
	minimap_x = MINIMAP_MARGIN;
	minimap_y = MINIMAP_MARGIN;
	// Create minimap background image
	game->minimap_bg = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!game->minimap_bg)
		return (0);
	// Create minimap player image (same size as background)
	game->minimap_player = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!game->minimap_player)
	{
		mlx_delete_image(game->mlx, game->minimap_bg);
		return (0);
	}
	// Add images to window
	if (mlx_image_to_window(game->mlx, game->minimap_bg, minimap_x,
			minimap_y) < 0)
	{
		mlx_delete_image(game->mlx, game->minimap_bg);
		mlx_delete_image(game->mlx, game->minimap_player);
		return (0);
	}
	if (mlx_image_to_window(game->mlx, game->minimap_player, minimap_x,
			minimap_y) < 0)
	{
		mlx_delete_image(game->mlx, game->minimap_bg);
		mlx_delete_image(game->mlx, game->minimap_player);
		return (0);
	}
	return (1);
}

/**
 * @brief Clean up minimap images
 * @param game The game structure
 */
void	cleanup_minimap(t_game *game)
{
	if (game->minimap_bg)
		mlx_delete_image(game->mlx, game->minimap_bg);
	if (game->minimap_player)
		mlx_delete_image(game->mlx, game->minimap_player);
}

/**
 * @brief Main minimap drawing function
 * @param game The game structure
 */
void	draw_minimap(t_game *game)
{
	if (!game->minimap_bg || !game->minimap_player)
		return ;
	// Always update background for smooth scrolling
	update_minimap_background(game);
	// Always update player position
	update_minimap_player(game);
}
