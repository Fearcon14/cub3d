/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:14:04 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/24 10:55:39 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup(t_game *game)
{
	if (game->mlx)
	{
		cleanup_minimap(game);
		mlx_delete_image(game->mlx, game->wall_textures[TEX_NORTH]);
		mlx_delete_image(game->mlx, game->wall_textures[TEX_SOUTH]);
		mlx_delete_image(game->mlx, game->wall_textures[TEX_EAST]);
		mlx_delete_image(game->mlx, game->wall_textures[TEX_WEST]);
		if (game->map && game->map->texture.north_texture)
			mlx_delete_texture(game->map->texture.north_texture);
		if (game->map && game->map->texture.south_texture)
			mlx_delete_texture(game->map->texture.south_texture);
		if (game->map && game->map->texture.east_texture)
			mlx_delete_texture(game->map->texture.east_texture);
		if (game->map && game->map->texture.west_texture)
			mlx_delete_texture(game->map->texture.west_texture);
		mlx_terminate(game->mlx);
	}
	free_gc();
}

/**
 * @brief Print error message and exit the program
 * @param msg The error message to display
 */
void	error_exit(t_game *game, char *msg)
{
	cleanup(game);
	ft_printf("Error\n%s", msg);
	// system("leaks -groupByType cub3d");
	exit(1);
}

// TODO: add shadows?
// TODO: Pokemon Textures
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		error_exit(&game, "Invalid number of arguments");
	if (ft_strlen(argv[1]) < 4 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4],
			".cub", 4) != 0)
	{
		error_exit(&game, "Invalid file extension (.cub expected)");
	}
	if (validate_map(argv[1], &game) == 0)
		error_exit(&game, "Invalid map");
	gc_free_context(VALIDATION);
	if (!c_init_game(&game))
		error_exit(&game, "Failed to initialize game");
	mlx_loop_hook(game.mlx, input_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_mouse_hook(game.mlx, mouse_hook, &game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mlx_close_hook(game.mlx, close_hook, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	// system("leaks -groupByType cub3d");
	return (0);
}
