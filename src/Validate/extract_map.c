/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinn <ksinn@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:14:08 by ksinn             #+#    #+#             */
/*   Updated: 2025/07/07 18:19:34 by ksinn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	skip_lines_before_map(t_extract_map *em, int lines_before_map)
{
	em->i = 0;
	while (em->i++ < lines_before_map)
	{
		em->line = get_next_line(em->fd);
		free(em->line);
	}
}

static void	skip_empty_lines(t_extract_map *em)
{
	em->line = get_next_line(em->fd);
	while (em->line && em->line[0] == '\n')
	{
		free(em->line);
		em->line = get_next_line(em->fd);
	}
}

static void	extract_map_lines(t_extract_map *em, t_game *game, t_valid_map *vm)
{
	em->i = 0;
	while (em->line)
	{
		if (em->line[0] == '\n')
		{
			vm->illegal_identifier = true;
			free(em->line);
			get_next_line(-1);
			close(em->fd);
			return ;
		}
		game->map->map[em->i++] = ft_strtrim(em->line, "\n");
		if (game->map->map[em->i - 1])
			gc_add_context(MAP, game->map->map[em->i - 1]);
		free(em->line);
		em->line = get_next_line(em->fd);
	}
}

void	c_extract_map(char *filename, t_game *game, int lines_before_map,
		t_valid_map *vm)
{
	t_extract_map	em;

	em.fd = open_map_file(game, filename);
	skip_lines_before_map(&em, lines_before_map);
	skip_empty_lines(&em);
	extract_map_lines(&em, game, vm);
	get_next_line(-1);
	close(em.fd);
}
