/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 00:58:52 by yoayedde          #+#    #+#             */
/*   Updated: 2025-01-23 00:58:52 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	move_player(t_map **map, int *a, int *b)
{
	if ((*map)->map[*a][*b] == 'N')
	{
		write(1, "you lost!!\n", 12);
		destroy_map(*map, NULL);
		exit(0);
	}
	if ((*map)->collected == (*map)->collectables && (*map)->map[*a][*b] == 'E')
	{
		write(1, "you WON!!\n", 11);
		destroy_map(*map, NULL);
		exit(0);
	}
	if ((*map)->map[*a][*b] == '1' || (*map)->map[*a][*b] == 'E')
		return (0);
	if ((*map)->map[*a][*b] == 'C')
		(*map)->collected += 1;
	if ((*map)->map[*a][*b] != 'E')
		(*map)->map[(*map)->x][(*map)->y] = '0';
	(*map)->map[*a][*b] = 'P';
	(*map)->x = *a;
	(*map)->y = *b;
	return (1);
}

int	key_detecotor(int keycode, t_map **map, int *a, int *b)
{
	if (keycode == KEY_W)
	{
		(*map)->facing = 1;
		*a -= 1;
	}
	else if (keycode == KEY_S)
	{
		(*map)->facing = 3;
		*a += 1;
	}
	else if (keycode == KEY_A)
	{
		(*map)->facing = 4;
		*b -= 1;
	}
	else if (keycode == KEY_D)
	{
		(*map)->facing = 2;
		*b += 1;
	}
	else
		return (0);
	return (1);
}

int	close_window(t_map *param)
{
	write(1, "Exiting...\n", 12);
	mlx_destroy_window(param->mlx, param->win);
	destroy_map(param, NULL);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_map *map)
{
	int		new_x;
	int		new_y;
	char	*movements;

	new_x = map->x;
	new_y = map->y;
	if (keycode == KEY_ESC)
		close_window(map);
	if (!key_detecotor(keycode, &map, &new_x, &new_y))
		return (0);
	if (move_player(&map, &new_x, &new_y) == 1)
	{
		movements = ft_itoa(map->moves);
		create_window(map, 0, 0);
		mlx_string_put(map->mlx, map->win, 5, 5, 0xFFFFFF, movements);
		free(movements);
		map->moves++;
	}
	return (0);
}

int	move_detector(t_map *map)
{
	map->collected = 0;
	mlx_key_hook(map->win, key_hook, map);
	mlx_hook(map->win, 17, 0, close_window, map);
	create_window(map, 0, 0);
	mlx_loop(map->mlx);
	return (0);
}
