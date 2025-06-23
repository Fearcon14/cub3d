/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:14:04 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/23 13:02:21 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup(t_game *game)
{
	free_gc();
	mlx_delete_image(game->mlx, game->wall_textures[TEX_NORTH]);
	mlx_delete_image(game->mlx, game->wall_textures[TEX_SOUTH]);
	mlx_delete_image(game->mlx, game->wall_textures[TEX_EAST]);
	mlx_delete_image(game->mlx, game->wall_textures[TEX_WEST]);
	mlx_terminate(game->mlx);
}

/**
 * @brief Print error message and exit the program
 * @param msg The error message to display
 */
void	error_exit(char *msg)
{
	free_gc();
	ft_printf("Error\n%s", msg);
	exit(1);
}
// TODO: add shadows?
int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	if (argc != 2)
		error_exit("Invalid number of arguments");
	if (ft_strlen(argv[1]) < 4 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4],
			".cub", 4) != 0)
	{
		error_exit("Invalid file extension (.cub expected)");
	}
	if (validate_map(argv[1], &map) == 0)
		error_exit("Invalid map");
	gc_free_context(VALIDATION);
	if (!c_init_game(&game, &map))
		error_exit("Failed to initialize game");
	mlx_loop_hook(game.mlx, input_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_mouse_hook(game.mlx, mouse_hook, &game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mlx_close_hook(game.mlx, close_hook, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
