/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:20:42 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/11 14:53:38 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "ft_printf.h"
# include "garbage_collector.h"
# include "get_next_line.h"
# include "libft.h"
# include "typedef.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_map
{
	char		**map;
	int			height;
	t_texture	texture;
}				t_map;

void			error_exit(char *msg);
int				validate_map(char *filename, t_map *map);

#endif
