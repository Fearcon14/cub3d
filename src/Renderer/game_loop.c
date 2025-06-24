/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:04:40 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/24 10:55:27 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	c_turn_fps_green(mlx_image_t *fps_img)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	pixel_index;

	i = 0;
	while (i < fps_img->height)
	{
		j = 0;
		while (j < fps_img->width)
		{
			pixel_index = (i * fps_img->width + j) * 4;
			if (fps_img->pixels[pixel_index + 3] > 0)
			{
				fps_img->pixels[pixel_index] = 0;
				fps_img->pixels[pixel_index + 1] = 255;
				fps_img->pixels[pixel_index + 2] = 0;
			}
			j++;
		}
		i++;
	}
}

void	game_loop(void *param)
{
	t_game				*game;
	int					fps;
	char				*fps_str;
	static mlx_image_t	*fps_img = NULL;

	game = (t_game *)param;
	raycast(game);
	draw_minimap(game);
	fps = (int)(1.0 / game->mlx->delta_time);
	fps_str = ft_itoa(fps);
	if (fps_img)
		mlx_delete_image(game->mlx, fps_img);
	fps_img = mlx_put_string(game->mlx, fps_str, SCREEN_WIDTH - 40, 15);
	c_turn_fps_green(fps_img);
	free(fps_str);
}
