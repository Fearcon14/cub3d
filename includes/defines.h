/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:07:57 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 10:55:23 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define FOV 60
# define MAX_RAY_DISTANCE 1000
# define MOVE_SPEED 0.07
# define ROTATION_SPEED 0.05
# define MOUSE_SENSITIVITY 0.003
# define PLAYER_OFFSET 0.2

// Minimap constants
# define MINIMAP_SIZE 200
# define MINIMAP_MARGIN 20
# define MINIMAP_GRID_SIZE 20
# define MINIMAP_CELL_SIZE 10

// Minimap colors (RGBA format: 0xRRGGBBAA)
# define MINIMAP_WALL_COLOR 0x333333FF
# define MINIMAP_FLOOR_COLOR 0xEEEEEEFF
# define MINIMAP_PLAYER_COLOR 0xFF0000FF
# define MINIMAP_DIRECTION_COLOR 0xFF6666FF
# define MINIMAP_BORDER_COLOR 0x000000FF

// Mathematical constants
# define PI 3.14159265359
# define PI_2 1.57079632679   // PI/2
# define TWO_PI 6.28318530718 // 2*PI

#endif
