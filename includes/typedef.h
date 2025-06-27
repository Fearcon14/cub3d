/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:18:38 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/27 14:40:42 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "MLX42/MLX42.h"
# include <stdbool.h>

// Gun animation constants
# define GUN_FRAME_COUNT 5
# define GUN_ANIMATION_DURATION 0.5
// Total animation duration in seconds
# define GUN_FRAME_DURATION (GUN_ANIMATION_DURATION / GUN_FRAME_COUNT)
// Duration per frame

typedef struct s_gun
{
	mlx_image_t		*frames[GUN_FRAME_COUNT];
	int				current_frame;
	bool			is_animating;
	double animation_time; // Current time in animation
	int				x_pos;
	int				y_pos;
}					t_gun;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_rect
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_rect;

typedef struct s_door
{
	int				x;
	int				y;
	bool			is_open;
}					t_door;

// legal_chars initialized to true
typedef struct s_valid_map
{
	bool			legal_chars;

	bool			walls_closed;

	bool			north_textured;
	bool			north_path_valid;

	bool			south_textured;
	bool			south_path_valid;

	bool			east_textured;
	bool			east_path_valid;

	bool			west_textured;
	bool			west_path_valid;

	bool			floor_colored;
	bool			floor_color_valid;

	bool			ceiling_colored;
	bool			ceiling_color_valid;

	int				player_placed;
	bool			map_allocated;
}					t_valid_map;

typedef struct s_texture
{
	char			*north_path;
	mlx_texture_t	*north_texture;
	char			*south_path;
	mlx_texture_t	*south_texture;
	char			*east_path;
	mlx_texture_t	*east_texture;
	char			*west_path;
	mlx_texture_t	*west_texture;

	int				floor_color;
	int				ceiling_color;
}					t_texture;

typedef struct s_map
{
	char			**map;
	int				height;
	t_texture		texture;
	t_door			*doors;
	int				door_count;
}					t_map;

typedef struct s_player
{
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
}					t_player;

typedef struct s_ray
{
	double camera_x;       // X coordinate on camera plane (-1 to +1)
	t_vector ray_dir;      // Ray direction vector
	t_vector map;          // Current map square (as doubles for calculations)
	t_vector side_dist;    // Distance from current position to next side
	t_vector delta_dist;   // Distance ray travels for 1 unit in X/Y
	double perp_wall_dist; // Perpendicular distance to wall
	t_vector step;         // Step direction (-1 or +1)
	int hit;               // Was a wall hit?
	int side;              // Which side was hit?
	int line_height;       // Height of wall line to draw
	int draw_start;        // Start pixel for wall drawing
	int draw_end;          // End pixel for wall drawing
}					t_ray;

// Texture mapping data
typedef struct s_tex_data
{
	int tex_num;    // Which texture to use (0=N, 1=S, 2=E, 3=W)
	double wall_x;  // Exact position where wall was hit
	int tex_x;      // X coordinate on texture
	double step;    // How much to increase tex_y per pixel
	double tex_pos; // Current texture Y position
}					t_tex_data;

// Main game/rendering data structure
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	t_player		player;
	mlx_image_t		*wall_textures[4];
	mlx_image_t		*door_texture;
	double			last_mouse_x;
	double			last_mouse_y;
	bool			mouse_init;
	bool			right_mouse_held;

	// Minimap images
	mlx_image_t		*minimap_bg;
	mlx_image_t		*minimap_player;

	// Gun system
	t_gun			gun;
}					t_game;

typedef enum e_tex_num
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_EAST,
	TEX_WEST
}					t_tex_num;

typedef struct s_door_data
{
	double			step_size;
	double			current_x;
	double			current_y;
	double			distance;
	int				steps;
	int				i;
	int				result;

}					t_door_data;

typedef struct s_wall_collision
{
	double			distance;
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
	int				map_x;
	int				map_y;
	double			closest_x;
	double			closest_y;
}					t_wall_collision;

typedef struct s_rgba
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_rgba;

typedef struct s_wall_render
{
	t_tex_data		tex;
	mlx_image_t		*wall_texture;
}					t_wall_render;

typedef struct s_extract_map
{
	int				fd;
	int				i;
	char			*line;
}					t_extract_map;

typedef struct s_point_visible
{
	double			dx;
	double			dy;
	double			distance;
	double			step_x;
	double			step_y;
	double			current_x;
	double			current_y;
	int				steps;
	int				i;
}					t_point_visible;

typedef struct s_vision_cone
{
	int				pixel_x;
	int				pixel_y;
	double			map_x;
	double			map_y;
	double			center_map_x;
	double			center_map_y;
	double			start_map_x;
	double			start_map_y;
}					t_vision_cone;

typedef struct s_minimap_background
{
	int				grid_x;
	int				grid_y;
	int				map_x;
	int				map_y;
	int				pixel_x;
	int				pixel_y;
	uint32_t		cell_color;
	double			center_map_x;
	double			center_map_y;
	double			start_map_x;
	double			start_map_y;
	double			offset_x;
	double			offset_y;
}					t_minimap_background;

#endif
