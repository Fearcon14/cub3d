/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:07:35 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 15:44:46 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	mouse_delta;

	game = (t_game *)param;
	// Initialize mouse position on first call
	if (!game->mouse_init)
	{
		game->last_mouse_x = xpos;
		game->last_mouse_y = ypos;
		game->mouse_init = true;
		return ;
	}
	// Calculate horizontal mouse movement (left/right)
	mouse_delta = xpos - game->last_mouse_x;
	// Only rotate if there's movement
	if (mouse_delta != 0.0)
		rotate_player_mouse(game, mouse_delta);
	// Update last mouse position
	game->last_mouse_x = xpos;
	game->last_mouse_y = ypos;
}
