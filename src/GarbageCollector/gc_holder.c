/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_holder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:49:53 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 13:54:41 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "garbage_collector.h"

/**
 * @brief Returns a pointer to the static array of garbage collection contexts
 *
 * This function provides access to the global static array that stores
 * all garbage collection contexts. The static array persists throughout
 * the program's execution, allowing memory to be tracked across function calls.
 *
 * @return Pointer to the static array of t_list pointers (garbage collection
 * contexts)
 */
t_list	**gc_holder(void)
{
	static t_list	*ptr[GC_ARR_SIZE] = {0};

	return (ptr);
}

t_game	*game_holder(void)
{
	static t_game	*game = {0};

	return (game);
}
