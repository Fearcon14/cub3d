/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:16:29 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/17 13:47:17 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

static void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

static void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.x * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

static void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.x * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

void	move_player(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W)
		move_forward(game);
	else if (keydata.key == MLX_KEY_S)
		move_backward(game);
	else if (keydata.key == MLX_KEY_A)
		move_left(game);
	else if (keydata.key == MLX_KEY_D)
		move_right(game);
	printf("Player position: %f, %f\n", game->player.pos.x, game->player.pos.y);
}
