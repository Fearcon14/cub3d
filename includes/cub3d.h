/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:20:42 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/12 15:50:06 by ksinn            ###   ########.fr       */
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
# include <stdio.h>
# include <stdlib.h>

// cub3d.c
void	error_exit(char *msg);

// validate.c
int		validate_map(char *filename, t_map *map);
void	c_extract_map(char *filename, t_map *tmap, int lines_before_map);
char	*c_extract_path(char *line);
int		c_extract_color(char *line, t_valid_map *vm, bool is_floor);

// process_line.c
void	c_process_line(char *line, t_valid_map *vm, t_map *tmap);

// parse_map.c
int		c_count_map_lines(char *filename, int *lines_before_map,
			t_valid_map *vm, t_map *tmap);
void	c_parse_map(char *filename, t_map *tmap, t_valid_map *vm);

// utils.c
int		open_map_file(char *filename);
void	c_free_split(char **split);
int		c_isspace(char c);

#endif
