/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:30:37 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/17 12:31:46 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c_init_wall_textures(t_game *game, t_texture *texture)
{
	game->wall_textures[TEX_NORTH] = mlx_texture_to_image(game->mlx,
			texture->north_texture);
	game->wall_textures[TEX_SOUTH] = mlx_texture_to_image(game->mlx,
			texture->south_texture);
	game->wall_textures[TEX_EAST] = mlx_texture_to_image(game->mlx,
			texture->east_texture);
	game->wall_textures[TEX_WEST] = mlx_texture_to_image(game->mlx,
			texture->west_texture);
}
