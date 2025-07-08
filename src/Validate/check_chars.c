/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:56:02 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/08 13:51:39 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c_check_chars(char **map, t_game *game)
{
	int	y;
	int	x;
	int	player_count;

	y = 0;
	player_count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr(" 012NSEW", map[y][x]))
				error_exit(game, "Illegal characters in map");
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error_exit(game, "Map must contain exactly one player");
}
