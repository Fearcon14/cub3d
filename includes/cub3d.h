/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:20:42 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/09 15:09:48 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include "typedef.h"
# include "libft.h"
# include "get_next_line.h"
# include "garbage_collector.h"
# include "ft_printf.h"
# include "MLX42/MLX42.h"

typedef struct s_map
{
    char **map;
    int width;
    int height;
} t_map;


void    error_exit(char *msg);
int     validate_map(char *filename);

#endif