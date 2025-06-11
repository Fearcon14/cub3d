/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:14:04 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/11 13:39:37 by ksinn            ###   ########.fr       */
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

// DONE: Map extension check should check ending not beginning of string
int	main(int argc, char **argv)
{
	if (argc != 2)
		error_exit("Invalid number of arguments");
	if (ft_strlen(argv[1]) < 4 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4],
			".cub", 4) != 0)
	{
		error_exit("Invalid file extension");
	}
	if (validate_map(argv[1]) == 0)
		error_exit("Invalid map");
	return (1);
}
