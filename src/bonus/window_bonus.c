/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:46:46 by mlezcano          #+#    #+#             */
/*   Updated: 2023/12/18 10:57:58 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_close_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy(game->mlx);
	exit(0);
}

void	ft_fill_floor(t_game *game)
{
	game->y = 0;
	while ((game->y) < (game->map_y))
	{
		game->x = 0;
		while ((game->x) < (game->map_x))
		{
			game->file = mlx_xpm_file_to_image(game->mlx,
					"./xpm/background.xpm", &game->pxl, &game->pxl);
			if (!game->file)
				err_exit();
			mlx_put_image_to_window (game->mlx, game->mlx_win,
				game->file, game->pxl * game->x,
				game->pxl * game->y);
			game->x++;
		}
		game->y++;
	}
}

int	ft_total_collect(t_game *game)
{
	int	i;

	i = 0;
	game->y = 0;
	while ((game->y) < (game->map_y))
	{
		game->x = 0;
		while ((game->x) < (game->map_x))
		{
			if (game->map[game->y][game->x] == 'C')
				i++;
			game->x++;
		}
		game->y++;
	}
	return (i);
}

void	ft_fill_window(t_game *game)
{
	game->collect = ft_total_collect(game);
	ft_fill_floor(game);
	game->y = 0;
	while ((game->y) < (game->map_y))
	{
		game->x = 0;
		while ((game->x) < (game->map_x))
		{
			if (game->map[game->y][game->x] == '1')
				ft_put_limits(game);
			if (game->map[game->y][game->x] == 'C')
				ft_put_collect(game);
			if (game->map[game->y][game->x] == 'P')
				ft_put_player(game);
			if (game->map[game->y][game->x] == 'E')
				ft_put_exit(game);
			if (game->map[game->y][game->x] == 'K')
				ft_put_enemy(game);
			game->x++;
		}
		game->y++;
	}
	ft_mov_display(game);
}
