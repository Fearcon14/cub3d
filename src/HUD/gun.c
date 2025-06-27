/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:53:38 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:20:00 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_gun_animation(t_game *game)
{
	if (!game->gun.is_animating)
	{
		game->gun.frames[0]->enabled = false;
		game->gun.is_animating = true;
		game->gun.current_frame = 0;
		game->gun.animation_time = 0.0;
		game->gun.frames[0]->enabled = true;
	}
}

void	update_gun_animation(t_game *game)
{
	int	new_frame;

	if (!game->gun.is_animating)
		return ;
	game->gun.animation_time += game->mlx->delta_time;
	new_frame = (int)(game->gun.animation_time / GUN_FRAME_DURATION);
	if (game->gun.animation_time >= GUN_ANIMATION_DURATION)
	{
		game->gun.frames[game->gun.current_frame]->enabled = false;
		game->gun.current_frame = 0;
		game->gun.is_animating = false;
		game->gun.animation_time = 0.0;
		game->gun.frames[0]->enabled = true;
		return ;
	}
	if (new_frame != game->gun.current_frame && new_frame < GUN_FRAME_COUNT)
	{
		game->gun.frames[game->gun.current_frame]->enabled = false;
		game->gun.current_frame = new_frame;
		game->gun.frames[game->gun.current_frame]->enabled = true;
	}
}

void	render_gun(t_game *game)
{
	update_gun_animation(game);
}

void	cleanup_gun(t_game *game)
{
	int	i;

	i = 0;
	while (i < GUN_FRAME_COUNT)
	{
		if (game->gun.frames[i])
			mlx_delete_image(game->mlx, game->gun.frames[i]);
		i++;
	}
}
