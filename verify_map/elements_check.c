#include "../so_long.h"

void	find_player(char **map, int *a, int *b)
{
	int	i;
	int	l;

	l = 0;
	while (map[l])
	{
		i = 0;
		while (map[l][i])
		{
			if (map[l][i] == 'P')
			{
				*a = l;
				*b = i;
				return ;
			}
			i++;
		}
		l++;
	}
	*a = -1;
	*b = -1;
}

int	is_valid(t_map *map, int x, int y)
{
	if (!map || !map->map)
		return (0);
	if (x < 0 || !map->map[x])
		return (0);
	if (y < 0 || !map->map[x][y])
		return (0);
	if (map->map[x][y] == '1')
		return (0);
	return (1);
}

void	bucket_fill(t_map **map, int x, int y, int *exit)
{
	if (*exit == 1)
		return ;
	if (is_valid((*map), x, y) == 0)
		return ;
	if ((*map)->map[x][y] == 'C')
		(*map)->collectables += 1;
	if ((*map)->map[x][y] == 'E')
	{
		(*map)->exit += 1;
		(*map)->map[x][y] = '1';
		return ;
	}
	if ((*map)->map[x][y] != '1')
		(*map)->map[x][y] = '1';
	bucket_fill(map, x, y + 1, exit);
	bucket_fill(map, x + 1, y, exit);
	bucket_fill(map, x, y - 1, exit);
	bucket_fill(map, x - 1, y, exit);
	return ;
}

int	count_elements(t_map **map)
{
	int	i;
	int	len;

	i = -1;
	len = -1;
	(*map)->collectables = 0;
	(*map)->character = 0;
	(*map)->exit = 0;
	while ((*map)->map[++i])
	{
		len = -1;
		while ((*map)->map[i][++len])
		{
			if ((*map)->map[i][len] == 'C')
				(*map)->collectables += 1;
			else if ((*map)->map[i][len] == 'P')
				(*map)->character += 1;
			else if ((*map)->map[i][len] == 'E')
				(*map)->exit += 1;
			else if ((*map)->map[i][len] != '1' && (*map)->map[i][len] != '0')
				return (0);
		}
	}
	return (1);
}

int	is_map_valid(t_map **original, t_map *copy)
{
	int	exit;

	exit = 0;
	if (!count_elements(original) || (*original)->character != 1
		|| (*original)->exit != 1 || (*original)->collectables < 1)
		return (perror("invalid elements\n"), 0);
	find_player(copy->map, &copy->x, &copy->y);
	find_player((*original)->map, &(*original)->x, &(*original)->y);
	copy->collectables = 0;
	copy->exit = 0;
	bucket_fill(&copy, copy->x, copy->y, &exit);
	if (copy->collectables != (*original)->collectables)
		return (perror("collectables or exit are not reachable\n"), 0);
	if (copy->exit != 1)
		return (perror("Exit not reachable\n"), 0);
	return (1);
}
