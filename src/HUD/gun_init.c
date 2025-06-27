/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:19:50 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/27 13:22:40 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_gun_textures(mlx_texture_t **textures)
{
	char	*frame_paths[GUN_FRAME_COUNT];
	int		i;

	frame_paths[0] = "assets/gun/frame_0.png";
	frame_paths[1] = "assets/gun/frame_1.png";
	frame_paths[2] = "assets/gun/frame_2.png";
	frame_paths[3] = "assets/gun/frame_3.png";
	frame_paths[4] = "assets/gun/frame_4.png";
	i = 0;
	while (i < GUN_FRAME_COUNT)
	{
		textures[i] = mlx_load_png(frame_paths[i]);
		if (!textures[i])
		{
			printf("Error: Failed to load gun frame %d from %s\n", i,
				frame_paths[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	convert_textures_to_images(t_game *game, mlx_texture_t **textures)
{
	int	i;

	i = 0;
	while (i < GUN_FRAME_COUNT)
	{
		game->gun.frames[i] = mlx_texture_to_image(game->mlx, textures[i]);
		mlx_delete_texture(textures[i]);
		if (!game->gun.frames[i])
		{
			printf("Error: Failed to convert gun frame %d to image\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	setup_gun_properties(t_game *game)
{
	game->gun.current_frame = 0;
	game->gun.is_animating = false;
	game->gun.animation_time = 0.0;
	game->gun.x_pos = (SCREEN_WIDTH - game->gun.frames[0]->width) / 2;
	game->gun.y_pos = SCREEN_HEIGHT - game->gun.frames[0]->height;
}

static int	add_gun_to_window(t_game *game)
{
	int	i;

	if (mlx_image_to_window(game->mlx, game->gun.frames[0], game->gun.x_pos,
			game->gun.y_pos) < 0)
	{
		printf("Error: Failed to add gun to window\n");
		return (0);
	}
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

int	init_gun(t_game *game)
{
	mlx_texture_t	*textures[GUN_FRAME_COUNT];

	if (!load_gun_textures(textures))
		return (0);
	if (!convert_textures_to_images(game, textures))
		return (0);
	setup_gun_properties(game);
	if (!add_gun_to_window(game))
		return (0);
	return (1);
}
