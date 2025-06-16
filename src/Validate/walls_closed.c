/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:56:29 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/16 13:15:10 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c_check_walls_closed(char **map, t_valid_map *vm)
{
	int	y;
	int	x;

	vm->walls_closed = true;
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
					vm->walls_closed = false;
					return ;
				}
			}
			x++;
		}
		y++;
	}
}
