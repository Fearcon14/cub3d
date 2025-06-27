/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:07:57 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 12:58:15 by ksinn            ###   ########.fr       */
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

// Door interaction constants
# define DOOR_INTERACTION_DISTANCE 1.5

// Minimap constants
# define MINIMAP_SIZE 200
# define MINIMAP_MARGIN 20
# define MINIMAP_GRID_SIZE 20
# define MINIMAP_CELL_SIZE 10

// Minimap colors (RGBA format: 0xRRGGBBAA)
# define MINIMAP_WALL_COLOR 0x333333C0
# define MINIMAP_FLOOR_COLOR 0xEEEEEEC0
# define MINIMAP_DOOR_COLOR 0x8B4513C0
# define MINIMAP_PLAYER_COLOR 0xFF0000C0
# define MINIMAP_BORDER_COLOR 0x000000C0

// Vision cone settings
# define MINIMAP_VISION_COLOR 0x40404040
# define MINIMAP_VISION_RANGE 5.0

# define PI 3.14159265359
# define PI_2 1.57079632679
# define TWO_PI 6.28318530718

#endif
