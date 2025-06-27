/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:33:31 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 14:40:05 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
 * @brief Check if a map coordinate is a wall or out of bounds
 * @param game The game structure
 * @param map_x X coordinate in map grid
 * @param map_y Y coordinate in map grid
 * @return 1 if wall/out of bounds, 0 if empty space
 */
int	is_wall_at(t_game *game, int map_x, int map_y)
{
	char	cell;

	if (map_y < 0 || map_y >= game->map->height)
		return (1);
	if (map_x < 0 || !game->map->map[map_y]
		|| map_x >= (int)ft_strlen(game->map->map[map_y]))
		return (1);
	cell = game->map->map[map_y][map_x];
	if (cell == '2')
	{
		return (!is_door_open(game, map_x, map_y));
	}
	return (cell != '0' && cell != 'N' && cell != 'S' && cell != 'E'
		&& cell != 'W');
}

/**
 * @brief Fill an entire image with a specific color
 * @param img The image to fill
 * @param color The color to fill with
 */
void	fill_image(mlx_image_t *img, uint32_t color)
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
 * @param rect Rectangle structure containing position and size
 * @param color Color to draw
 */
void	draw_rect(mlx_image_t *img, t_rect rect, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < rect.height)
	{
		x = 0;
		while (x < rect.width)
		{
			if (rect.x + x >= 0 && rect.x + x < (int)img->width && rect.y
				+ y >= 0 && rect.y + y < (int)img->height)
			{
				mlx_put_pixel(img, rect.x + x, rect.y + y, color);
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
void	draw_minimap_border(mlx_image_t *img)
{
	uint32_t	i;

	i = 0;
	while (i < img->width)
	{
		mlx_put_pixel(img, i, 0, MINIMAP_BORDER_COLOR);
		mlx_put_pixel(img, i, img->height - 1, MINIMAP_BORDER_COLOR);
		i++;
	}
	i = 0;
	while (i < img->height)
	{
		mlx_put_pixel(img, 0, i, MINIMAP_BORDER_COLOR);
		mlx_put_pixel(img, img->width - 1, i, MINIMAP_BORDER_COLOR);
		i++;
	}
}
