/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:38 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:55:50 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_texture_coordinates(t_game *game, t_ray *ray, t_tex_data *tex,
		mlx_image_t **selected_texture)
{
	mlx_image_t	*wall_texture;
	int			tex_width;
	int			tex_height;

	if (game->map->map[(int)ray->map.y][(int)ray->map.x] == '2'
		&& game->door_texture)
		wall_texture = game->door_texture;
	else
		wall_texture = game->wall_textures[ray->side];
	*selected_texture = wall_texture;
	if (ray->side == TEX_NORTH || ray->side == TEX_SOUTH)
		tex->wall_x = game->player.pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	else
		tex->wall_x = game->player.pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	tex->wall_x -= floor(tex->wall_x);
	tex_width = wall_texture->width;
	tex_height = wall_texture->height;
	tex->tex_x = (int)(tex->wall_x * tex_width);
	if (tex->tex_x >= tex_width)
		tex->tex_x = tex_width - 1;
	tex->step = (double)tex_height / ray->line_height;
	tex->tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* tex->step;
}
