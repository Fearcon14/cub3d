/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:18:38 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/11 14:20:40 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// legal_chars initialized to true
typedef struct s_valid_map
{
	bool	legal_chars;

	bool	walls_closed;

	bool	north_textured;
	bool	north_path_valid;

	bool	south_textured;
	bool	south_path_valid;

	bool	east_textured;
	bool	east_path_valid;

	bool	west_textured;
	bool	west_path_valid;

	bool	floor_colored;
	bool	floor_colour_valid;

	bool	ceiling_colored;
	bool	ceiling_colour_valid;

	int		player_placed;
}			t_valid_map;

typedef struct s_texture
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;

	int		floor_color;
	int		ceiling_color;
}			t_texture;
