/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:53:38 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 13:01:22 by ksinn            ###   ########.fr       */
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
	game->gun.animation_counter = 0;
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
		game->gun.is_animating = true;
		game->gun.current_frame = 0;
		game->gun.animation_counter = 0;
	}
}

void	update_gun_animation(t_game *game)
{
	if (!game->gun.is_animating)
		return ;
	game->gun.animation_counter++;
	// Check if it's time to advance to the next frame
	if (game->gun.animation_counter >= GUN_ANIMATION_SPEED)
	{
		// Hide current frame
		game->gun.frames[game->gun.current_frame]->enabled = false;
		// Advance to next frame
		game->gun.current_frame++;
		game->gun.animation_counter = 0;
		// Check if animation is complete
		if (game->gun.current_frame >= GUN_FRAME_COUNT)
		{
			game->gun.current_frame = 0;
			game->gun.is_animating = false;
		}
		// Show new current frame
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
