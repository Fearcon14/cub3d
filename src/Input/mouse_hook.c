/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:07:19 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 16:02:50 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_RIGHT)
	{
		if (action == MLX_PRESS)
		{
			game->mouse_init = false;
			game->right_mouse_held = true;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		}
		else if (action == MLX_RELEASE)
		{
			game->mouse_init = false;
			game->right_mouse_held = false;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		}
	}
	(void)mods;
	return ;
}
