/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:25:15 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/20 14:42:51 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: change to 4 different colors
static uint32_t	get_wall_color(t_ray *ray)
{
	if (ray->side == TEX_NORTH)
		return (0x006600FF);
	else if (ray->side == TEX_SOUTH)
		return (0x660000FF);
	else if (ray->side == TEX_EAST)
		return (0x000066FF);
	else if (ray->side == TEX_WEST)
		return (0xFFFFFFFF);
	else
		return (0x000000FF);
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
