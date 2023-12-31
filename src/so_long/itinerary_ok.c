/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itinerary_ok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:53:27 by mlezcano          #+#    #+#             */
/*   Updated: 2023/12/17 19:57:13 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_anyone_there(t_game *game, char **map)
{
	while (game->itinerary_perso_y < game->map_y)
	{
		game->itinerary_perso_x = 0;
		while (game->itinerary_perso_x < game->map_x)
		{
			if (map[game->itinerary_perso_y][game->itinerary_perso_x] == 'P')
				return (1);
			game->itinerary_perso_x++;
		}
		game->itinerary_perso_y++;
	}
	return (0);
}

void	iti_collects(t_game *game, char **map, int x, int y)
{
	if (map[y][x] == 'C')
		game->itinerary_items++;
	if (map[y - 1][x] == '0' || map[y + 1][x] == '0' || map[y][x - 1] == '0'
			|| map[y][x + 1] == '0' || map[y - 1][x] == 'C'
			|| map[y + 1][x] == 'C' || map[y][x - 1] == 'C'
			|| map[y][x + 1] == 'C')
		map[y][x] = '.';
	if (map[y - 1][x] == '0' || map[y - 1][x] == 'C')
		iti_collects(game, map, x, y - 1);
	if (map[y + 1][x] == '0' || map[y + 1][x] == 'C')
		iti_collects(game, map, x, y + 1);
	if (map[y][x - 1] == '0' || map[y][x - 1] == 'C')
		iti_collects(game, map, x - 1, y);
	if (map[y][x + 1] == '0' || map[y][x + 1] == 'C')
		iti_collects(game, map, x + 1, y);
	map[y][x] = '.';
}

void	iti_exit(t_game *game, char **map, int x, int y)
{
	if (map[y][x] == 'E')
		game->itinerary_exit++;
	if (map[y - 1][x] == '0' || map[y + 1][x] == '0' || map[y][x - 1] == '0'
			|| map[y][x + 1] == '0' || map[y - 1][x] == 'C'
			|| map[y + 1][x] == 'C' || map[y][x - 1] == 'C'
			|| map[y][x + 1] == 'C')
		map[y][x] = '.';
	if (map[y - 1][x] == '0' || map[y - 1][x] == 'C' || map[y - 1][x] == 'E')
		iti_exit(game, map, x, y - 1);
	if (map[y + 1][x] == '0' || map[y + 1][x] == 'C' || map[y + 1][x] == 'E')
		iti_exit(game, map, x, y + 1);
	if (map[y][x - 1] == '0' || map[y][x - 1] == 'C' || map[y][x - 1] == 'E')
		iti_exit(game, map, x - 1, y);
	if (map[y][x + 1] == '0' || map[y][x + 1] == 'C' || map[y][x + 1] == 'E')
		iti_exit(game, map, x + 1, y);
	map[y][x] = '.';
}

void	ft_copy_map(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_y)
	{
		map[i] = (char *)malloc(sizeof(char) * (game->map_x + 1));
		if (!map[i])
			err_exit();
		i++;
	}
	i = 0;
	while (i < game->map_y)
	{
		j = 0;
		while (j < game->map_x)
		{
			map[i][j] = game->map[i][j];
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
}

int	ft_itinerary_ok(t_game *game)
{
	int		line;
	char	**map;

	line = 0;
	map = (char **)malloc(sizeof(char *) * (game->map_y + 1));
	if (!map)
		err_exit();
	ft_copy_map(game, map);
	if (!ft_anyone_there(game, map))
		return (free_2_array(map), 0);
	iti_collects(game, map, game->itinerary_perso_x, game->itinerary_perso_y);
	if (game->itinerary_items != game->collect)
		return (free_2_array(map), printer(MAP_ERR_EXIT), 0);
	while (line < game->map_y)
		free(map[line++]);
	ft_copy_map(game, map);
	iti_exit(game, map, game->itinerary_perso_x, game->itinerary_perso_y);
	line = 0;
	free_2_array(map);
	if (game->itinerary_exit != 1)
		return (printer(MAP_ERR_EXIT), 0);
	return (1);
}
