#include "../so_long.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(1, &s[i], fd);
		i++;
	}
	write(1, "\n", 1);
}
