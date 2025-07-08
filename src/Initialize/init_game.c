/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:35:15 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/08 14:40:39 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c_init_game(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (0);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		return (0);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	c_init_player(game);
	c_init_wall_textures(game, &game->map->texture);
	door_init(game);
	if (!init_minimap(game))
		return (0);
	if (!init_gun(game))
		return (0);
	game->mouse_init = false;
	game->last_mouse_x = 0.0;
	game->last_mouse_y = 0.0;
	game->right_mouse_held = false;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	return (1);
}
