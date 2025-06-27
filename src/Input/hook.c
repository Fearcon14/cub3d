/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:48:10 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/20 12:50:51 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	raycast(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx,
			MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_A)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) || mlx_is_key_down(game->mlx,
			MLX_KEY_RIGHT))
		rotate_player(game);
}
