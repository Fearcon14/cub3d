/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:25:15 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 14:05:03 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_texture_pixel(mlx_image_t *texture, int tex_x, int tex_y)
{
	int		pixel_index;
	uint8_t	*pixel_data;
	t_rgba	color;

	tex_x = tex_x % texture->width;
	tex_y = tex_y % texture->height;
	if (tex_x < 0)
		tex_x += texture->width;
	if (tex_y < 0)
		tex_y += texture->height;
	pixel_index = (tex_y * texture->width + tex_x) * 4;
	pixel_data = &texture->pixels[pixel_index];
	color.r = pixel_data[0];
	color.g = pixel_data[1];
	color.b = pixel_data[2];
	color.a = pixel_data[3];
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}

static void	render_ceiling_slice(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(game->img, x, y, game->map->texture.ceiling_color);
		y++;
	}
}

static void	render_wall_pixels(t_game *game, t_ray *ray,
		t_wall_render *wall_render, int x)
{
	int			y;
	uint32_t	color;
	int			tex_y;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)wall_render->tex.tex_pos;
		tex_y = tex_y % wall_render->wall_texture->height;
		if (tex_y < 0)
			tex_y += wall_render->wall_texture->height;
		color = get_texture_pixel(wall_render->wall_texture,
				wall_render->tex.tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		wall_render->tex.tex_pos += wall_render->tex.step;
		y++;
	}
}

static void	render_floor_slice(t_game *game, int x, int draw_end)
{
	int	y;

	y = draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->img, x, y, game->map->texture.floor_color);
		y++;
	}
}

void	render_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_wall_render	wall_render;

	calculate_texture_coordinates(game, ray, &wall_render.tex,
		&wall_render.wall_texture);
	render_ceiling_slice(game, x, ray->draw_start);
	render_wall_pixels(game, ray, &wall_render, x);
	render_floor_slice(game, x, ray->draw_end);
}
