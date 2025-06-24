/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:32:53 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 11:01:31 by ksinn            ###   ########.fr       */
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
	return (cell != '0' && cell != 'N' && cell != 'S' && cell != 'E'
		&& cell != 'W');
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
			if (is_wall_at(game, map_x, map_y))
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
	int		player_pixel_x;
	int		player_pixel_y;
	int		dir_end_x;
	int		dir_end_y;
	int		i;
	double	t;
	int		line_x;
	int		line_y;

	// Clear the player image
	fill_image(game->minimap_player, 0x00000000); // Transparent
	// Player is always at the center of the minimap
	player_pixel_x = MINIMAP_SIZE / 2;
	player_pixel_y = MINIMAP_SIZE / 2;
	// Draw player dot (3x3 red square)
	draw_rect(game->minimap_player, player_pixel_x - 1, player_pixel_y - 1, 3,
		3, MINIMAP_PLAYER_COLOR);
	// Draw direction line
	dir_end_x = player_pixel_x + (int)(game->player.dir.x * 15);
	dir_end_y = player_pixel_y + (int)(game->player.dir.y * 15);
	// Simple line drawing
	i = 0;
	while (i <= 15)
	{
		t = i / 15.0;
		line_x = player_pixel_x + (int)(t * (dir_end_x - player_pixel_x));
		line_y = player_pixel_y + (int)(t * (dir_end_y - player_pixel_y));
		if (line_x >= 0 && line_x < (int)game->minimap_player->width
			&& line_y >= 0 && line_y < (int)game->minimap_player->height)
		{
			mlx_put_pixel(game->minimap_player, line_x, line_y,
				MINIMAP_DIRECTION_COLOR);
		}
		i++;
	}
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
