/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:35:15 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 14:46:05 by ksinn            ###   ########.fr       */
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
	return (1);
}
