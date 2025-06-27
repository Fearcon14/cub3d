/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:19:34 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 14:48:40 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_w_e(t_game *game, double fov_factor, int dir)
{
	if (dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = -game->player.dir.y * fov_factor;
		game->player.plane.y = game->player.dir.x * fov_factor;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = -game->player.dir.y * fov_factor;
		game->player.plane.y = game->player.dir.x * fov_factor;
	}
	else
		error_exit(game, "Player direction was unintialised!");
}

static void	set_player_dir(char dir, t_game *game)
{
	double	fov_factor;

	fov_factor = tan(FOV * PI / 360.0);
	if (dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = -game->player.dir.y * fov_factor;
		game->player.plane.y = game->player.dir.x * fov_factor;
	}
	else if (dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -game->player.dir.y * fov_factor;
		game->player.plane.y = game->player.dir.x * fov_factor;
	}
	else
		set_player_w_e(game, fov_factor, dir);
}

static void	get_player(t_game *game)
{
	int		y;
	int		x;
	char	dir;

	y = 0;
	dir = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == 'N' || game->map->map[y][x] == 'S'
				|| game->map->map[y][x] == 'E' || game->map->map[y][x] == 'W')
			{
				dir = game->map->map[y][x];
				game->player.pos.x = x + 0.5;
				game->player.pos.y = y + 0.5;
				break ;
			}
			x++;
		}
		y++;
	}
	set_player_dir(dir, game);
}

void	c_init_player(t_game *game)
{
	get_player(game);
}
