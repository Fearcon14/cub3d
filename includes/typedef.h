/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:18:38 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/12 15:04:28 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// legal_chars initialized to true
typedef struct s_valid_map
{
	bool		legal_chars;

	bool		walls_closed;

	bool		north_textured;
	bool		north_path_valid;

	bool		south_textured;
	bool		south_path_valid;

	bool		east_textured;
	bool		east_path_valid;

	bool		west_textured;
	bool		west_path_valid;

	bool		floor_colored;
	bool		floor_color_valid;

	bool		ceiling_colored;
	bool		ceiling_color_valid;

	int			player_placed;
}				t_valid_map;

typedef struct s_texture
{
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;

	int			floor_color;
	int			ceiling_color;
}				t_texture;

typedef struct s_map
{
	char		**map;
	int			height;
	t_texture	texture;
}				t_map;
