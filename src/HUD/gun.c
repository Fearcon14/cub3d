/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:53:38 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 13:12:34 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_gun(t_game *game)
{
	char			*frame_paths[GUN_FRAME_COUNT];
	mlx_texture_t	*texture;
	int				i;

	// Initialize frame paths
	frame_paths[0] = "assets/gun/frame_0.png";
	frame_paths[1] = "assets/gun/frame_1.png";
	frame_paths[2] = "assets/gun/frame_2.png";
	frame_paths[3] = "assets/gun/frame_3.png";
	frame_paths[4] = "assets/gun/frame_4.png";
	// Load all gun frame textures and convert to images
	i = 0;
	while (i < GUN_FRAME_COUNT)
	{
		texture = mlx_load_png(frame_paths[i]);
		if (!texture)
		{
			printf("Error: Failed to load gun frame %d from %s\n", i,
				frame_paths[i]);
			return (0);
		}
		game->gun.frames[i] = mlx_texture_to_image(game->mlx, texture);
		mlx_delete_texture(texture);
		if (!game->gun.frames[i])
		{
			printf("Error: Failed to convert gun frame %d to image\n", i);
			return (0);
		}
		i++;
	}
	// Initialize gun state
	game->gun.current_frame = 0;
	game->gun.is_animating = false;
	game->gun.animation_time = 0.0;
	// Position gun at bottom center of screen
	game->gun.x_pos = (SCREEN_WIDTH - game->gun.frames[0]->width) / 2;
	game->gun.y_pos = SCREEN_HEIGHT - game->gun.frames[0]->height;
	// Add the default frame to the display
	if (mlx_image_to_window(game->mlx, game->gun.frames[0], game->gun.x_pos,
			game->gun.y_pos) < 0)
	{
		printf("Error: Failed to add gun to window\n");
		return (0);
	}
	// Hide all other frames initially
	i = 1;
	while (i < GUN_FRAME_COUNT)
	{
		if (mlx_image_to_window(game->mlx, game->gun.frames[i], game->gun.x_pos,
				game->gun.y_pos) < 0)
		{
			printf("Error: Failed to add gun frame %d to window\n", i);
			return (0);
		}
		game->gun.frames[i]->enabled = false;
		i++;
	}
	return (1);
}

void	start_gun_animation(t_game *game)
{
	if (!game->gun.is_animating)
	{
		// Hide frame 0 before starting animation
		game->gun.frames[0]->enabled = false;
		game->gun.is_animating = true;
		game->gun.current_frame = 0;
		game->gun.animation_time = 0.0;
		// Show frame 0 to start the animation
		game->gun.frames[0]->enabled = true;
	}
}

void	update_gun_animation(t_game *game)
{
	int	new_frame;

	if (!game->gun.is_animating)
		return ;
	// Add delta time to animation time
	game->gun.animation_time += game->mlx->delta_time;
	// Calculate which frame we should be on based on elapsed time
	new_frame = (int)(game->gun.animation_time / GUN_FRAME_DURATION);
	// Check if we've completed the animation
	if (game->gun.animation_time >= GUN_ANIMATION_DURATION)
	{
		// Hide current frame
		game->gun.frames[game->gun.current_frame]->enabled = false;
		// Reset to frame 0 and stop animation
		game->gun.current_frame = 0;
		game->gun.is_animating = false;
		game->gun.animation_time = 0.0;
		// Show frame 0
		game->gun.frames[0]->enabled = true;
		return ;
	}
	// If we need to advance to a new frame
	if (new_frame != game->gun.current_frame && new_frame < GUN_FRAME_COUNT)
	{
		// Hide current frame
		game->gun.frames[game->gun.current_frame]->enabled = false;
		// Update to new frame
		game->gun.current_frame = new_frame;
		// Show new frame
		game->gun.frames[game->gun.current_frame]->enabled = true;
	}
}

void	render_gun(t_game *game)
{
	update_gun_animation(game);
}

void	cleanup_gun(t_game *game)
{
	int	i;

	i = 0;
	while (i < GUN_FRAME_COUNT)
	{
		if (game->gun.frames[i])
			mlx_delete_image(game->mlx, game->gun.frames[i]);
		i++;
	}
}
