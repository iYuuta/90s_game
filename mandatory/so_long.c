#include "so_long.h"

void	put_texture(t_map *map, char *str, int x, int y)
{
	int	a;
	int	b;
	void *picture;

	picture = mlx_xpm_file_to_image(map->mlx, str, &a, &b);
	if (!picture)
		clean_up(map);
	mlx_put_image_to_window(map->mlx, map->win, picture, x, y);
	mlx_destroy_image(map->mlx, picture);
}

char	**read_map(int fd)
{
	char	*lines;
	char	*tmp;
	char	**map;

	tmp = NULL;
	lines = get_next_line(fd);
	if (lines == NULL)
	{
		free (lines);
		close(fd);
		return (NULL);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		if (tmp[0] == '\n')
			return (close(fd), free(tmp), free(lines), NULL);
		lines = ft_strjoin(&lines, tmp);
		free(tmp);
	}
	close(fd);
	map = ft_split(lines, '\n');
	return (free(lines), map);
}

void	create_window(t_map *m, int a, int b)
{

	a = -1;
	while (m->map[++a])
	{
		b = -1;
		while (m->map[a][++b])
		{
			if (m->map[a][b] == '0')
				put_texture(m, "textures/floor.xpm", b * 32, a * 32);
			else if (m->map[a][b] == '1')
				put_texture(m, "textures/wall.xpm", b * 32, a * 32);
			else if (m->map[a][b] == 'P')
				put_texture(m, "textures/player_front.xpm", b * 32, a * 32);
			else if (m->map[a][b] == 'C')
				put_texture(m, "textures/coin.xpm", b * 32, a * 32);
			else if (m->map[a][b] == 'E' && m->collectables != m->collected)
				put_texture(m, "textures/portal.xpm", b * 32, a * 32);
			else
				put_texture(m, "textures/portal2.xpm", b * 32, a * 32);
		}
	}
}

int	main(int ac, char **av)
{
	t_map		*maps;
	int			fd;

	if (ac != 2)
		return (write(2, "you didn't add a map\n", 22), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (close(fd), write(2, "invalid file\n", 14), 0);
	maps = check_map(fd);
	if (maps == NULL)
		return (write(2, "invalid map\n", 13), 0);
	maps->moves = 1;
	maps->mlx = mlx_init();
	if (!maps->mlx)
		return (destroy_map(maps, NULL), write(2, "error\n", 7), 0);
	maps->win = mlx_new_window(maps->mlx, 32 * maps->length,
			32 * maps->width, "so_long");
	if (!maps->win)
		return (free(maps->mlx), destroy_map(maps, NULL), write(2, "error\n", 7), 0);
	move_detector(maps);
	mlx_loop(maps->mlx);
}
