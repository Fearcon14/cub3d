/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:22:09 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 14:53:07 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_map_errors(t_valid_map *vm)
{
	if (!vm->legal_chars)
		ft_putstr_fd("Error: Illegal characters in map\n", 2);
	if (!vm->walls_closed)
		ft_putstr_fd("Error: Walls are not closed\n", 2);
	if (vm->player_placed != 1)
	{
		ft_putstr_fd("Error: You have placed ", 2);
		ft_putnbr_fd(vm->player_placed, 2);
		ft_putstr_fd(" players in the map\n", 2);
	}
}

static void	print_texture_errors(t_valid_map *vm)
{
	if (!vm->north_path_valid)
		ft_putstr_fd("Error: Invalid north path\n", 2);
	if (!vm->north_textured)
		ft_putstr_fd("Error: North path is not textured\n", 2);
	if (!vm->south_path_valid)
		ft_putstr_fd("Error: Invalid south path\n", 2);
	if (!vm->south_textured)
		ft_putstr_fd("Error: South path is not textured\n", 2);
	if (!vm->east_path_valid)
		ft_putstr_fd("Error: Invalid east path\n", 2);
	if (!vm->east_textured)
		ft_putstr_fd("Error: East path is not textured\n", 2);
	if (!vm->west_path_valid)
		ft_putstr_fd("Error: Invalid west path\n", 2);
	if (!vm->west_textured)
		ft_putstr_fd("Error: West path is not textured\n", 2);
}

static void	print_color_errors(t_valid_map *vm)
{
	if (!vm->floor_color_valid)
		ft_putstr_fd("Error: Invalid floor color\n", 2);
	if (!vm->ceiling_color_valid)
		ft_putstr_fd("Error: Invalid ceiling color\n", 2);
}

static int	check_validation_status(t_valid_map *vm)
{
	if (!vm->legal_chars || !vm->walls_closed || vm->player_placed != 1)
		return (0);
	if (!vm->north_path_valid || !vm->north_textured)
		return (0);
	if (!vm->south_path_valid || !vm->south_textured)
		return (0);
	if (!vm->east_path_valid || !vm->east_textured)
		return (0);
	if (!vm->west_path_valid || !vm->west_textured)
		return (0);
	if (!vm->floor_color_valid || !vm->ceiling_color_valid)
		return (0);
	return (1);
}

int	print_errors(t_valid_map *vm)
{
	if (!vm->map_allocated)
		ft_putstr_fd("Error: Map allocation failed\n", 2);
	print_map_errors(vm);
	print_texture_errors(vm);
	print_color_errors(vm);
	return (check_validation_status(vm));
}
