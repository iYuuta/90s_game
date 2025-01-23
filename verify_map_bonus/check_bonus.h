#ifndef CHECK_BONUS_H
# define CHECK_BONUS_H

# include "../so_long_bonus.h"

int		is_valid(t_map *map, int x, int y);
void	bucket_fill(t_map **map, int x, int y, int *exit);
void	find_player(char **map, int *a, int *b);
int		count_elements(t_map **map);
int		is_map_valid(t_map **original, t_map *copy);
void	destroy_map(t_map *dup, t_map *map);
t_map	*check_map(int fd);

#endif