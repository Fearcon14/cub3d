/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:25:15 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 12:45:30 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_texture_coordinates(t_game *game, t_ray *ray,
		t_tex_data *tex, mlx_image_t **selected_texture)
{
	mlx_image_t	*wall_texture;
	int			tex_width;
	int			tex_height;

	// Determine which texture will be used BEFORE calculating coordinates
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

static uint32_t	get_texture_pixel(mlx_image_t *texture, int tex_x, int tex_y)
{
	int		pixel_index;
	uint8_t	*pixel_data;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	tex_x = tex_x % texture->width;
	tex_y = tex_y % texture->height;
	if (tex_x < 0)
		tex_x += texture->width;
	if (tex_y < 0)
		tex_y += texture->height;
	pixel_index = (tex_y * texture->width + tex_x) * 4;
	pixel_data = &texture->pixels[pixel_index];
	r = pixel_data[0];
	g = pixel_data[1];
	b = pixel_data[2];
	a = pixel_data[3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	render_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_tex_data	tex;
	mlx_image_t	*wall_texture;
	int			y;
	uint32_t	color;
	int			tex_y;

	calculate_texture_coordinates(game, ray, &tex, &wall_texture);
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(game->img, x, y, game->map->texture.ceiling_color);
		y++;
	}
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex.tex_pos;
		tex_y = tex_y % wall_texture->height;
		if (tex_y < 0)
			tex_y += wall_texture->height;
		color = get_texture_pixel(wall_texture, tex.tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		tex.tex_pos += tex.step;
		y++;
	}
	y = ray->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->img, x, y, game->map->texture.floor_color);
		y++;
	}
}
