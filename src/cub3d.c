/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:14:04 by rmakoni           #+#    #+#             */
/*   Updated: 2025/06/09 14:28:46 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Print error message and exit the program
 * @param msg The error message to display
 */
void    error_exit(char *msg)
{
    ft_printf("Error\n%s", msg);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        error_exit("Invalid number of arguments");
    if (ft_strncmp(argv[1], ".cub", 4) != 0)
        error_exit("Invalid file extension");
    if (validate_map(argv[1]) == 0)
        error_exit("Invalid map");
    return 1;
}
