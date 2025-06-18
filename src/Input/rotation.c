/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:16:44 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/18 12:56:10 by ksinn            ###   ########.fr       */
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

void	rotate_player(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT)
		rotate_left(game);
	else if (keydata.key == MLX_KEY_RIGHT)
		rotate_right(game);
	rotate_camera_plane(game);
}
