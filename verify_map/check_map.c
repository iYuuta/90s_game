#include "../so_long.h"
#include "check.h"

t_map	*duplicate_map(t_map *data)
{
	t_map	*dup_map;
	char	**dup;
	int		i;
	int		l;

	i = 0;
	dup_map = malloc(sizeof(t_map));
	dup = (char **)malloc(sizeof(char *) * (data->width + 1));
	while (i < data->width)
		dup[i++] = (char *)malloc(data->length + 1);
	dup[i] = 0;
	l = 0;
	while (l < data->width)
	{
		i = 0;
		while (i < data->length)
		{
			dup[l][i] = data->map[l][i];
			i++;
		}
		dup[l][i] = '\0';
		l++;
	}
	return (dup_map->map = dup, dup_map);
}

t_map	*map_data(int fd, t_map *maps)
{
	maps->map = read_map(fd);
	if (maps->map == NULL)
	{
		free(maps);
		return (NULL);
	}
	maps->width = -1;
	while (maps->map[++maps->width])
	{
		maps->length = -1;
		while (maps->map[maps->width][++maps->length])
		{
			if (maps->map[maps->width][maps->length] == 'C')
				maps->collectables += 1;
			else if (maps->map[maps->width][maps->length] == 'P')
				maps->character += 1;
			else if (maps->map[maps->width][maps->length] == 'E')
				maps->exit += 1;
		}
	}
	return (maps);
}

void	destroy_map(t_map *dup, t_map *map)
{
	int	i;

	i = 0;
	while (dup->map[i])
		free(dup->map[i++]);
	free(dup->map);
	free(dup);
	if (map != NULL)
		destroy_map(map, NULL);
}

int	check_borders(t_map *map)
{
	int	i;
	int	l;

	l = 0;
	while (map->map[l])
	{
		i = 0;
		while (map->map[l][i])
		{
			if (map->map[0][i] != '1' || map->map[map->width - 1][i] != '1'
			|| map->map[l][0] != '1' || map->map[l][map->length - 1] != '1')
				return (0);
			i++;
		}
		l++;
	}
	return (1);
}

t_map	*check_map(int fd)
{
	t_map	*dup;
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->collectables = 0;
	map->exit = 0;
	map = map_data(fd, map);
	if (map == NULL)
	{
		free(map);
		return (NULL);
	}
	dup = duplicate_map(map);
	if (is_map_valid(&map, dup) == 0 || check_borders(map) == 0)
	{
		destroy_map(dup, map);
		return (NULL);
	}
	else
	{
		destroy_map(dup, NULL);
		return (map);
	}
}
