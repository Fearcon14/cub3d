/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:45:18 by ksinn             #+#    #+#             */
/*   Updated: 2025/06/23 13:52:41 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "libft.h"
# include <stdlib.h>
# define GC_ARR_SIZE 2

typedef struct s_game	t_game;

typedef enum e_gc_context
{
	VALIDATION,
	MAP
}						t_gc_context;

// gc_malloc.c
void					*gc_malloc(size_t size);
void					free_gc(void);
void					gc_add_context(t_gc_context context, void *ptr);

// gc_free_context.c
void					gc_free_context(t_gc_context context);

// gc_holder.c
t_list					**gc_holder(void);
t_game					*game_holder(void);

#endif
