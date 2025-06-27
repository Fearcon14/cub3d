/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:32:53 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 14:41:14 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**

* @brief Check if a point is visible from the player position
		(simple line-of-sight check)
 * @param game The game structure
 * @param target_x Target X coordinate in map space
 * @param target_y Target Y coordinate in map space
 * @return 1 if visible, 0 if blocked by wall
 */
static int	is_point_visible(t_game *game, double target_x, double target_y)
{
	t_point_visible	pv;

	pv.dx = target_x - game->player.pos.x;
	pv.dy = target_y - game->player.pos.y;
	pv.distance = sqrt(pv.dx * pv.dx + pv.dy * pv.dy);
	if (pv.distance > MINIMAP_VISION_RANGE)
		return (0);
	pv.steps = (int)(pv.distance * 10);
	if (pv.steps <= 0)
		return (1);
	pv.step_x = pv.dx / pv.steps;
	pv.step_y = pv.dy / pv.steps;
	pv.current_x = game->player.pos.x;
	pv.current_y = game->player.pos.y;
	pv.i = 0;
	while (pv.i < pv.steps)
	{
		pv.current_x += pv.step_x;
		pv.current_y += pv.step_y;
		if (is_wall_at(game, (int)pv.current_x, (int)pv.current_y))
			return (0);
		pv.i++;
	}
	return (1);
}

/**
 * @brief Check if a point is within the player's field of view cone
 * @param game The game structure
 * @param target_x Target X coordinate in map space
 * @param target_y Target Y coordinate in map space
 * @return 1 if within FOV, 0 if outside
 */
static int	is_in_fov(t_game *game, double target_x, double target_y)
{
	t_vector	delta;
	double		target_angle;
	double		player_angle;
	double		angle_diff;
	double		half_fov_rad;

	delta.x = target_x - game->player.pos.x;
	delta.y = target_y - game->player.pos.y;
	target_angle = atan2(delta.y, delta.x);
	player_angle = atan2(game->player.dir.y, game->player.dir.x);
	angle_diff = target_angle - player_angle;
	while (angle_diff > PI)
		angle_diff -= TWO_PI;
	while (angle_diff < -PI)
		angle_diff += TWO_PI;
	half_fov_rad = (FOV * PI / 180.0) / 2.0;
	return (fabs(angle_diff) <= half_fov_rad);
}

/**
 * @brief Draw the vision cone overlay
 * @param game The game structure
 */
void	draw_vision_cone(t_game *game)
{
	t_vision_cone	vc;

	vc.center_map_x = game->player.pos.x;
	vc.center_map_y = game->player.pos.y;
	vc.start_map_x = vc.center_map_x - MINIMAP_GRID_SIZE / 2.0;
	vc.start_map_y = vc.center_map_y - MINIMAP_GRID_SIZE / 2.0;
	vc.pixel_y = 1;
	while (vc.pixel_y < MINIMAP_SIZE - 1)
	{
		vc.pixel_x = 0;
		while (++vc.pixel_x < MINIMAP_SIZE - 1)
		{
			vc.map_x = vc.start_map_x + (double)(vc.pixel_x - 1)
				/ MINIMAP_CELL_SIZE;
			vc.map_y = vc.start_map_y + (double)(vc.pixel_y - 1)
				/ MINIMAP_CELL_SIZE;
			if (is_in_fov(game, vc.map_x, vc.map_y) && is_point_visible(game,
					vc.map_x, vc.map_y))
			{
				mlx_put_pixel(game->minimap_player, vc.pixel_x, vc.pixel_y,
					MINIMAP_VISION_COLOR);
			}
		}
		vc.pixel_y++;
	}
}

/**
 * @brief Main minimap drawing function
 * @param game The game structure
 */
void	draw_minimap(t_game *game)
{
	if (!game->minimap_bg || !game->minimap_player)
		return ;
	update_minimap_background(game);
	update_minimap_player(game);
}
