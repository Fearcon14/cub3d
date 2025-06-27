/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:40:13 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:43:53 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir.x = game->player.dir.x + game->player.plane.x * ray->camera_x;
	ray->ray_dir.y = game->player.dir.y + game->player.plane.y * ray->camera_x;
	ray->map.x = (int)game->player.pos.x;
	ray->map.y = (int)game->player.pos.y;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->hit = 0;
}

static void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y)
			* ray->delta_dist.y;
	}
}

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(game, &ray, x);
		calculate_step_and_side_dist(game, &ray);
		dda(game, &ray);
		calculate_wall_distance(game, &ray);
		calculate_wall_height(&ray);
		render_wall_slice(game, &ray, x);
		x++;
	}
}
