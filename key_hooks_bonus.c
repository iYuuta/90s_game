#include "so_long_bonus.h"
#include "verify_map_bonus/check_bonus.h"

int	move_player(t_map **map, int *a, int *b)
{
	if ((*map)->map[*a][*b] == 'N')
	{
		write(1, "you lost nigga!!\n", 18);
		destroy_map(*map, NULL);
		exit(0);
	}
	if ((*map)->collected == (*map)->collectables && (*map)->map[*a][*b] == 'E')
	{
		write(1, "you WON nigga!!\n", 17);
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

void	update_movement(t_map *map)
{
	char	*movements;

	movements = ft_itoa(map->moves);
	create_window(map, 0, 0);
	mlx_string_put(map->mlx, map->win, 5, 5, 0xFFFFFF, movements);
	free(movements);
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

int	key_hook(int keycode, t_map *map)
{
	int	new_x;
	int	new_y;

	new_x = map->x;
	new_y = map->y;
	if (keycode == KEY_ESC)
	{
		printf("Escape key pressed! Exiting...\n");
		mlx_destroy_window(map->mlx, map->win);
		destroy_map(map, NULL);
		exit(0);
	}
	if (!key_detecotor(keycode, &map, &new_x, &new_y))
		return (0);
	if (move_player(&map, &new_x, &new_y) == 1)
	{
		update_movement(map);
		map->moves++;
	}
	return (0);
}

int	move_detector(t_map *map)
{
	map->collected = 0;
	mlx_key_hook(map->win, key_hook, map);
	create_window(map, 0, 0);
	mlx_loop(map->mlx);
	return (0);
}
