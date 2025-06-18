/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:20:42 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/18 12:32:17 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "defines.h"
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

// check_chars.c
void	c_check_chars(char **map, t_valid_map *vm);

// paths_valid.c
void	c_check_paths_valid(t_texture *texture, t_valid_map *vm);

// walls_closed.c
void	c_check_walls_closed(char **map, t_valid_map *vm);

// print_error.c
int		print_errors(t_valid_map *vm);

// init_player.c
void	c_init_player(t_player *player, t_map *map);

// init_game.c
int		c_init_game(t_game *game, t_map *map);

// init_wall_texture.c
void	c_init_wall_textures(t_game *game, t_texture *texture);

// key_hook.c
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

// mouse_hook.c
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
			void *param);

// cursor_hook.c
void	cursor_hook(double xpos, double ypos, void *param);

// game_loop.c
void	game_loop(void *param);

// movement.c
void	move_player(t_game *game, mlx_key_data_t keydata);

// rotation.c
void	rotate_player(t_game *game, mlx_key_data_t keydata);

// raycast.c
void	raycast(t_game *game);

// dda.c
void	dda(t_game *game, t_ray *ray);

#endif
