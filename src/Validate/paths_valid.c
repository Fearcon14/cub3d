/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:57:03 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/16 14:14:24 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c_check_paths_valid(t_texture *texture, t_valid_map *vm)
{
	texture->north_texture = mlx_load_png(texture->north_path);
	if (texture->north_texture)
		vm->north_path_valid = true;
	texture->south_texture = mlx_load_png(texture->south_path);
	if (texture->south_texture)
		vm->south_path_valid = true;
	texture->east_texture = mlx_load_png(texture->east_path);
	if (texture->east_texture)
		vm->east_path_valid = true;
	texture->west_texture = mlx_load_png(texture->west_path);
	if (texture->west_texture)
		vm->west_path_valid = true;
}
