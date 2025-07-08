/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:57:03 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/08 13:51:41 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c_check_paths_valid(t_texture *texture, t_game *game)
{
	texture->north_texture = mlx_load_png(texture->north_path);
	if (!texture->north_texture)
		error_exit(game, "Invalid north texture path");
	texture->south_texture = mlx_load_png(texture->south_path);
	if (!texture->south_texture)
		error_exit(game, "Invalid south texture path");
	texture->east_texture = mlx_load_png(texture->east_path);
	if (!texture->east_texture)
		error_exit(game, "Invalid east texture path");
	texture->west_texture = mlx_load_png(texture->west_path);
	if (!texture->west_texture)
		error_exit(game, "Invalid west texture path");
}
