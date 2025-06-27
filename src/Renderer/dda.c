/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:30:39 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:43:18 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Step the ray to the next grid boundary in either X or Y direction
 * @param ray The ray structure containing step distances and directions
 * @return 1 if stepped in X direction, 0 if stepped in Y direction
 */
static int	step_ray_to_next_grid(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		return (1);
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		return (0);
	}
}

/**
 * @brief Determine which wall side was hit based on step direction
 * @param ray The ray structure to update with the correct texture side
 * @param stepped_x 1 if ray stepped in X direction, 0 if in Y direction
 */
static void	determine_wall_side(t_ray *ray, int stepped_x)
{
	if (stepped_x)
	{
		if (ray->step.x > 0)
			ray->side = TEX_EAST;
		else
			ray->side = TEX_WEST;
	}
	else
	{
		if (ray->step.y > 0)
			ray->side = TEX_SOUTH;
		else
			ray->side = TEX_NORTH;
	}
}

/**
 * @brief Check if the current ray position hits a wall or closed door
 * @param game The game structure containing map data
 * @param ray The ray structure containing current map position
 * @return 1 if wall/closed door is hit, 0 if position is clear
 */
static int	check_wall_collision(t_game *game, t_ray *ray)
{
	char	cell;

	cell = game->map->map[(int)ray->map.y][(int)ray->map.x];
	if (cell == '1')
		return (1);
	if (cell == '2')
	{
		if (!is_door_open(game, (int)ray->map.x, (int)ray->map.y))
			return (1);
	}
	return (0);
}

/**
 * @brief DDA algorithm for raycasting - steps through grid until wall is hit
 * @param game The game structure containing map and door data
 * @param ray The ray structure to process
 */
void	dda(t_game *game, t_ray *ray)
{
	int	stepped_x;

	while (ray->hit == 0)
	{
		stepped_x = step_ray_to_next_grid(ray);
		determine_wall_side(ray, stepped_x);
		if (check_wall_collision(game, ray))
			ray->hit = 1;
	}
}
