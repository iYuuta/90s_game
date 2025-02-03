#ifndef SO_LONG_UTILS_H
# define SO_LONG_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 10

char	*duplicate(char *str);
void	ft_putstr_fd(char *s, int fd);
void	*free_em(char **ptr1, char **ptr2);
int		ft_strlength(char *str);
int		check(char *str);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char **s1, char const *s2);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);

#endif