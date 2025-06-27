/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:27:28 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 14:45:06 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Clean up minimap images on error
 * @param game The game structure
 */
static void	cleanup_minimap_on_error(t_game *game)
{
	if (game->minimap_bg)
		mlx_delete_image(game->mlx, game->minimap_bg);
	if (game->minimap_player)
		mlx_delete_image(game->mlx, game->minimap_player);
	game->minimap_bg = NULL;
	game->minimap_player = NULL;
}

/**
 * @brief Create minimap images
 * @param game The game structure
 * @return 1 on success, 0 on failure
 */
static int	create_minimap_images(t_game *game)
{
	game->minimap_bg = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!game->minimap_bg)
		return (0);
	game->minimap_player = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!game->minimap_player)
	{
		mlx_delete_image(game->mlx, game->minimap_bg);
		game->minimap_bg = NULL;
		return (0);
	}
	return (1);
}

/**
 * @brief Add minimap images to window at specified position
 * @param game The game structure
 * @param x X position for the minimap
 * @param y Y position for the minimap
 * @return 1 on success, 0 on failure
 */
static int	add_minimap_to_window(t_game *game, int x, int y)
{
	if (mlx_image_to_window(game->mlx, game->minimap_bg, x, y) < 0)
	{
		cleanup_minimap_on_error(game);
		return (0);
	}
	if (mlx_image_to_window(game->mlx, game->minimap_player, x, y) < 0)
	{
		cleanup_minimap_on_error(game);
		return (0);
	}
	return (1);
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

	minimap_x = MINIMAP_MARGIN;
	minimap_y = MINIMAP_MARGIN;
	if (!create_minimap_images(game))
		return (0);
	if (!add_minimap_to_window(game, minimap_x, minimap_y))
		return (0);
	return (1);
}
