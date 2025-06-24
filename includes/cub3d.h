/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:20:42 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/24 10:55:33 by ksinn            ###   ########.fr       */
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
void	error_exit(t_game *game, char *msg);

// validate.c
int		validate_map(char *filename, t_game *game);
void	c_extract_map(char *filename, t_game *game, int lines_before_map);
char	*c_extract_path(t_game *game, char *line);
int		c_extract_color(t_game *game, char *line, t_valid_map *vm,
			bool is_floor);

// process_line.c
void	c_process_line(char *line, t_valid_map *vm, t_game *game);

// parse_map.c
int		c_count_map_lines(char *filename, int *lines_before_map,
			t_valid_map *vm, t_game *game);
void	c_parse_map(char *filename, t_game *game, t_valid_map *vm);

// utils.c
int		open_map_file(t_game *game, char *filename);
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
void	c_init_player(t_game *game);

// init_game.c
int		c_init_game(t_game *game);

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

// hook.c
void	input_hook(void *param);

// movement.c
void	move_player(t_game *game);

// wall_collision.c
int		is_wall_collision(t_game *game, double x, double y);

// rotation.c
void	rotate_player(t_game *game);
void	rotate_player_mouse(t_game *game, double mouse_delta);

// minimap.c
void	draw_minimap(t_game *game);
int		init_minimap(t_game *game);
void	cleanup_minimap(t_game *game);

// raycast.c
void	raycast(t_game *game);

// dda.c
void	dda(t_game *game, t_ray *ray);

// wall_calc.c
void	calculate_wall_distance(t_game *game, t_ray *ray);
void	calculate_wall_height(t_ray *ray);

// wall_render.c
void	render_wall_slice(t_game *game, t_ray *ray, int x);

#endif
