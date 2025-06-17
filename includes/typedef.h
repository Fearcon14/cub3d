/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:18:38 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/17 10:46:34 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

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
}					t_map;

typedef struct s_player
{
	t_vector		pos;
	t_vector		dir;
	t_vector plane; // Camera plane vector (perpendicular to direction)
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
	int side;              // Which side was hit? (0=NS wall, 1=EW wall)
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
	mlx_image_t *img; // Main render image
	t_map			*map;
	t_player		player;
	mlx_image_t *wall_textures[4]; // Wall texture images [N,S,E,W]
	int				screen_width;
	int				screen_height;
}					t_game;

typedef enum e_tex_num
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_EAST,
	TEX_WEST
}					t_tex_num;
