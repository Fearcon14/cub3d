/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:25:15 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/18 15:07:52 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_wall_color(t_ray *ray)
{
	if (ray->side == SIDE_NS)
	{
		return (0xFF0000FF); // Red (RGBA)
	}
	else
	{
		return (0x800000FF); // Dark red (RGBA)
	}
}

void	render_wall_slice(t_game *game, t_ray *ray, int x)
{
	uint32_t	color;
	int			y;

	color = get_wall_color(ray);
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(game->img, x, y, game->map->texture.ceiling_color);
		y++;
	}
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->img, x, y, game->map->texture.floor_color);
		y++;
	}
}
