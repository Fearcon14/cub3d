/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:20:42 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/08 13:51:48 by ksinn            ###   ########.fr       */
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
char	*c_extract_path(t_game *game, char *line);
int		c_extract_color(t_game *game, char *line);

// extract_map.c
void	c_extract_map(char *filename, t_game *game, int lines_before_map);

// process_line.c
void	c_process_line(char *line, t_game *game);

// parse_map.c
int		c_count_map_lines(char *filename, int *lines_before_map, t_game *game);
void	c_parse_map(char *filename, t_game *game);

// utils.c
int		open_map_file(t_game *game, char *filename);
void	c_free_split(char **split);
int		c_isspace(char c);

// check_chars.c
void	c_check_chars(char **map, t_game *game);

// paths_valid.c
void	c_check_paths_valid(t_texture *texture, t_game *game);

// walls_closed.c
void	c_check_walls_closed(char **map, t_game *game);

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

// wall_collision_init.c
void	setup_collision_bounds(t_wall_collision *wc, double x, double y);

// rotation.c
void	rotate_player(t_game *game);
void	rotate_camera_plane(t_game *game);

// rotate_mouse.c
void	rotate_player_mouse(t_game *game, double mouse_delta);

// minimap.c
void	draw_minimap(t_game *game);
void	draw_vision_cone(t_game *game);

// init_minimap.c
int		init_minimap(t_game *game);

// minimap_utils.c
void	cleanup_minimap(t_game *game);
void	fill_image(mlx_image_t *img, uint32_t color);
int		is_wall_at(t_game *game, int map_x, int map_y);
void	draw_rect(mlx_image_t *img, t_rect rect, uint32_t color);
void	draw_minimap_border(mlx_image_t *img);

// update_minimap.c
void	update_minimap_background(t_game *game);

// update_minimap_player.c
void	update_minimap_player(t_game *game);

// raycast.c
void	raycast(t_game *game);

// dda.c
void	dda(t_game *game, t_ray *ray);

// wall_calc.c
void	calculate_wall_distance(t_game *game, t_ray *ray);
void	calculate_wall_height(t_ray *ray);

// wall_render.c
void	render_wall_slice(t_game *game, t_ray *ray, int x);

// wall_render_helper.c
void	calculate_texture_coordinates(t_game *game, t_ray *ray, t_tex_data *tex,
			mlx_image_t **selected_texture);

// door.c
void	door_interact(t_game *game);
int		is_door_at(t_game *game, int x, int y);
int		is_door_open(t_game *game, int x, int y);
int		player_facing_door(t_game *game, int *door_x, int *door_y);

// door_init.c
void	door_init(t_game *game);

// gun.c
void	render_gun(t_game *game);
void	start_gun_animation(t_game *game);
void	update_gun_animation(t_game *game);
void	cleanup_gun(t_game *game);

// gun_init.c
int		init_gun(t_game *game);

#endif
