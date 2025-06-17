/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:14:04 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/17 12:35:04 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Print error message and exit the program
 * @param msg The error message to display
 */
void	error_exit(char *msg)
{
	ft_printf("Error\n%s", msg);
	exit(1);
}

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
	if (!c_init_game(&game, &map))
		error_exit("Failed to initialize game");
	mlx_loop(game.mlx);
	return (1);
}
