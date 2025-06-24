/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:30:39 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 12:36:35 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			if (ray->step.x > 0)
				ray->side = TEX_EAST;
			else
				ray->side = TEX_WEST;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			if (ray->step.y > 0)
				ray->side = TEX_SOUTH;
			else
				ray->side = TEX_NORTH;
		}
		if (game->map->map[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = 1;
		// Check for doors - only closed doors stop the ray
		if (game->map->map[(int)ray->map.y][(int)ray->map.x] == '2')
		{
			if (!is_door_open(game, (int)ray->map.x, (int)ray->map.y))
				ray->hit = 1;
		}
	}
}
