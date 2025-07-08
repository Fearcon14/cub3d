/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:56:29 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/08 13:51:43 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c_check_walls_closed(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
			{
				if (y == 0 || !map[y + 1] || x == 0 || !map[y][x + 1] || map[y
					- 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x
					- 1] == ' ' || map[y][x + 1] == ' ')
				{
					error_exit(game, "Walls are not closed");
				}
			}
			x++;
		}
		y++;
	}
}
