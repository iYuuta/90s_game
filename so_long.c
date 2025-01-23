#include "so_long.h"

int	initialize_textures(t_textures *t, void **mlx)
{
	int	a;
	int	b;

	t->f = mlx_xpm_file_to_image(*mlx, "textures/floor.xpm", &a, &b);
	t->w = mlx_xpm_file_to_image(*mlx, "textures/wall.xpm", &a, &b);
	t->e = mlx_xpm_file_to_image(*mlx, "textures/portal.xpm", &a, &b);
	t->e2 = mlx_xpm_file_to_image(*mlx, "textures/portal2.xpm", &a, &b);
	t->c = mlx_xpm_file_to_image(*mlx, "textures/coin.xpm", &a, &b);
	t->p = mlx_xpm_file_to_image(*mlx, "textures/p_front.xpm", &a, &b);
	t->n = mlx_xpm_file_to_image(*mlx, "textures/enemy.xpm", &a, &b);
	if (!t->f || !t->w || !t->e || !t->e2 || !t->c || !t->p || !t->n)
		return (0);
	return (1);
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
		lines = ft_strjoin(&lines, tmp);
		free(tmp);
	}
	close(fd);
	map = ft_split(lines, '\n');
	free(lines);
	return (map);
}

void	create_window(t_map *m, int a, int b)
{
	t_textures	t;

	initialize_textures(&t, &(m->mlx));
	a = -1;
	while (m->map[++a])
	{
		b = -1;
		while (m->map[a][++b])
		{
			if (m->map[a][b] == '0')
				mlx_put_image_to_window(m->mlx, m->win, t.f, b * 32, a * 32);
			else if (m->map[a][b] == '1')
				mlx_put_image_to_window(m->mlx, m->win, t.w, b * 32, a * 32);
			else if (m->map[a][b] == 'P')
				mlx_put_image_to_window(m->mlx, m->win, t.p, b * 32, a * 32);
			else if (m->map[a][b] == 'N')
				mlx_put_image_to_window(m->mlx, m->win, t.n, b * 32, a * 32);
			else if (m->map[a][b] == 'C')
				mlx_put_image_to_window(m->mlx, m->win, t.c, b * 32, a * 32);
			else if (m->map[a][b] == 'E' && m->collectables != m->collected)
				mlx_put_image_to_window(m->mlx, m->win, t.e, b * 32, a * 32);
			else
				mlx_put_image_to_window(m->mlx, m->win, t.e2, b * 32, a * 32);
		}
	}
}

int	main(int ac, char **av)
{
	t_map		*maps;
	t_textures	tmp;
	int			fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("invalid file\n"), 0);
	maps = check_map(fd);
	if (maps == NULL)
		return (perror("empty map\n"), 0);
	maps->moves = 0;
	maps->mlx = mlx_init();
	maps->win = mlx_new_window(maps->mlx, 32 * maps->length,
			32 * maps->width, "so_long");
	if (!initialize_textures(&tmp, &(maps->mlx)))
		exit(0);
	move_detector(maps);
	mlx_loop(maps->mlx);
}
