#include "so_long.h"

int	move_player(t_map **map, int *a, int *b)
{
	void	*portal;

	if ((*map)->collected == (*map)->collectables && (*map)->map[*a][*b] == 'E')
	{
		portal = mlx_xpm_file_to_image((*map)->mlx,
				"textures/portal.xpm", a, b);
		write(1, "you won nigga!!!\n", 18);
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

void	update_movement(t_map **map)
{
	char	*movements;

	(*map)->moves += 1;
	movements = ft_itoa((*map)->moves);
	create_window((*map), 0, 0);
	ft_putstr_fd(movements, 1);
	free(movements);
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
		exit(0);
	}
	if (keycode == KEY_W)
		new_x -= 1;
	else if (keycode == KEY_S)
		new_x += 1;
	else if (keycode == KEY_A)
		new_y -= 1;
	else if (keycode == KEY_D)
		new_y += 1;
	else
		return (0);
	if (move_player(&map, &new_x, &new_y) == 1)
		update_movement(&map);
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
