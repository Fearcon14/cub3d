/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:19:34 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/17 12:25:36 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_w_e(t_player *player, double fov_factor, int dir)
{
	if (dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = -player->dir.y * fov_factor;
		player->plane.y = player->dir.x * fov_factor;
	}
	else if (dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = -player->dir.y * fov_factor;
		player->plane.y = player->dir.x * fov_factor;
	}
}

static void	set_player_dir(char dir, t_player *player)
{
	double	fov_factor;

	fov_factor = tan(FOV * PI / 360.0);
	if (dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = -player->dir.y * fov_factor;
		player->plane.y = player->dir.x * fov_factor;
	}
	else if (dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -player->dir.y * fov_factor;
		player->plane.y = player->dir.x * fov_factor;
	}
	else
		set_player_w_e(player, fov_factor, dir);
}

static void	get_player(t_map *map, t_player *player)
{
	int		y;
	int		x;
	char	dir;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				dir = map->map[y][x];
				player->pos.x = x + 0.5;
				player->pos.y = y + 0.5;
				break ;
			}
			x++;
		}
		y++;
	}
	set_player_dir(dir, player);
}

void	c_init_player(t_player *player, t_map *map)
{
	get_player(map, player);
}
