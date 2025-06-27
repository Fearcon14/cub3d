/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_minimap_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:47:56 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 14:48:06 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Update the player indicator position and direction
 * @param game The game structure
 */
void	update_minimap_player(t_game *game)
{
	int	player_pixel_x;
	int	player_pixel_y;

	fill_image(game->minimap_player, 0x00000000);
	draw_vision_cone(game);
	player_pixel_x = MINIMAP_SIZE / 2;
	player_pixel_y = MINIMAP_SIZE / 2;
	draw_rect(game->minimap_player, (t_rect){player_pixel_x - 1, player_pixel_y
		- 1, 3, 3}, MINIMAP_PLAYER_COLOR);
}
