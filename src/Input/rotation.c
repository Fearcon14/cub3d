/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:16:44 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 15:44:57 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_camera_plane(t_game *game)
{
	double	fov_factor;

	fov_factor = tan(FOV * PI / 360.0);
	game->player.plane.x = -game->player.dir.y * fov_factor;
	game->player.plane.y = game->player.dir.x * fov_factor;
}

static void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(ROTATION_SPEED)
		- game->player.dir.y * sin(ROTATION_SPEED);
	game->player.dir.y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir.y
		* cos(-ROTATION_SPEED);
	game->player.plane.x = game->player.plane.x * cos(ROTATION_SPEED)
		- game->player.plane.y * sin(ROTATION_SPEED);
	game->player.plane.y = old_plane_x * sin(ROTATION_SPEED)
		+ game->player.plane.y * cos(ROTATION_SPEED);
}

static void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(-ROTATION_SPEED)
		- game->player.dir.y * sin(-ROTATION_SPEED);
	game->player.dir.y = old_dir_x * sin(-ROTATION_SPEED) + game->player.dir.y
		* cos(-ROTATION_SPEED);
	game->player.plane.x = game->player.plane.x * cos(-ROTATION_SPEED)
		- game->player.plane.y * sin(-ROTATION_SPEED);
	game->player.plane.y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player.plane.y * cos(-ROTATION_SPEED);
}

static void	rotate_by_angle(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y
		* sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y
		* cos(angle);
	game->player.plane.x = game->player.plane.x * cos(angle)
		- game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y
		* cos(angle);
}

void	rotate_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	rotate_camera_plane(game);
}

void	rotate_player_mouse(t_game *game, double mouse_delta)
{
	double	rotation_angle;

	rotation_angle = mouse_delta * MOUSE_SENSITIVITY;
	rotate_by_angle(game, rotation_angle);
	rotate_camera_plane(game);
}
