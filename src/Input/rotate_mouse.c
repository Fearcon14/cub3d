/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:30:35 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:31:47 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	rotate_player_mouse(t_game *game, double mouse_delta)
{
	double	rotation_angle;

	rotation_angle = mouse_delta * MOUSE_SENSITIVITY;
	rotate_by_angle(game, rotation_angle);
	rotate_camera_plane(game);
}
