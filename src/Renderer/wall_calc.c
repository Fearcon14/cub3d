/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:50:15 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/18 14:53:37 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == SIDE_NS)
	{
		ray->perp_wall_dist = (ray->map.x - game->player.pos.x + (1
					- ray->step.x) / 2) / ray->ray_dir.x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map.y - game->player.pos.y + (1
					- ray->step.y) / 2) / ray->ray_dir.y;
	}
}

void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}
