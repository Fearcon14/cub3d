/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:40:02 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:40:16 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_collision_bounds(t_wall_collision *wc, double x, double y)
{
	wc->min_x = (int)floor(x - PLAYER_OFFSET);
	wc->max_x = (int)floor(x + PLAYER_OFFSET);
	wc->min_y = (int)floor(y - PLAYER_OFFSET);
	wc->max_y = (int)floor(y + PLAYER_OFFSET);
}
