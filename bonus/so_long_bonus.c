/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 01:00:29 by yoayedde          #+#    #+#             */
/*   Updated: 2025-01-23 01:00:29 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	player_facing(t_map *map, t_textures t, int a, int b)
{
	if (map->facing == 1)
		mlx_put_image_to_window(map->mlx, map->win, t.p_1, b * 32, a * 32);
	else if (map->facing == 2)
		mlx_put_image_to_window(map->mlx, map->win, t.p_2, b * 32, a * 32);
	else if (map->facing == 4)
		mlx_put_image_to_window(map->mlx, map->win, t.p_4, b * 32, a * 32);
	else
		mlx_put_image_to_window(map->mlx, map->win, t.p_3, b * 32, a * 32);
}

int	initialize_textures(t_textures *texture, void **mlx)
{
	int	a;
	int	b;

	texture->f = mlx_xpm_file_to_image(*mlx, "textures/floor.xpm", &a, &b);
	texture->w = mlx_xpm_file_to_image(*mlx, "textures/wall.xpm", &a, &b);
	texture->e = mlx_xpm_file_to_image(*mlx, "textures/portal.xpm", &a, &b);
	texture->e2 = mlx_xpm_file_to_image(*mlx, "textures/portal2.xpm", &a, &b);
	texture->c = mlx_xpm_file_to_image(*mlx, "textures/coin.xpm", &a, &b);
	texture->p_3 = mlx_xpm_file_to_image(*mlx, "textures/p_front.xpm", &a, &b);
	texture->p_1 = mlx_xpm_file_to_image(*mlx,
			"textures/player_back.xpm", &a, &b);
	texture->p_4 = mlx_xpm_file_to_image(*mlx,
			"textures/player_left.xpm", &a, &b);
	texture->p_2 = mlx_xpm_file_to_image(*mlx,
			"textures/player_right.xpm", &a, &b);
	texture->n = mlx_xpm_file_to_image(*mlx, "textures/enemy.xpm", &a, &b);
	if (!texture->f || !texture->w || !texture->e || !texture->e2
		|| !texture->c || !texture->p_1 || !texture->p_2
		|| !texture->p_3 || !texture->p_4 || !texture->n)
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
		if (tmp[0] == '\n')
			return (free(tmp), free(lines), NULL);
		lines = ft_strjoin(&lines, tmp);
		free(tmp);
	}
	close(fd);
	map = ft_split(lines, '\n');
	return (free(lines), map);
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
				player_facing(m, t, a, b);
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
		return (write(2, "you didn't add a map\n", 22), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (close(fd), write(2, "invalid file\n", 14), 0);
	maps = check_map(fd);
	if (maps == NULL)
		return (write(2, "invalid map\n", 13), 0);
	maps->moves = 1;
	maps->mlx = mlx_init();
	maps->win = mlx_new_window(maps->mlx, 32 * maps->length,
			32 * maps->width, "so_long_bonus");
	if (!initialize_textures(&tmp, &(maps->mlx)))
		exit(0);
	move_detector(maps);
	mlx_loop(maps->mlx);
}
