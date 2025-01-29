#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <mlx.h>
# include <stdlib.h> 
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "../utilities/so_long_utils.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1 
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_map
{
	int		moves;
	int		facing;
	char	**map;
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		length;
	int		width;
	int		collectables;
	int		collected;
	int		exit;
	int		character;
}	t_map;

typedef struct s_textures
{
	int		*moves;
	void	*f;
	void	*w;
	void	*e;
	void	*e2;
	void	*c;
	void	*p;
	void	*n;
}	t_textures;

char	**read_map(int fd);
void	create_window(t_map *map, int a, int b);
t_map	*check_map(int fd);
int		move_detector(t_map *map);
int		is_valid(t_map *map, int x, int y);
void	bucket_fill(t_map **map, int x, int y, int *exit);
void	find_player(char **map, int *a, int *b);
int		count_elements(t_map **map);
int		is_map_valid(t_map **original, t_map *copy);
void	destroy_map(t_map *dup, t_map *map);

#endif