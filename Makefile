SRCS = so_long.c key_hooks.c verify_map/check_map.c verify_map/elements_check.c \
       utilities/ft_itoa.c utilities/ft_putstr_fd.c utilities/ft_split.c \
       utilities/ft_strdup.c utilities/ft_strjoin.c utilities/ft_strlcpy.c \
       utilities/ft_strlen.c utilities/ft_substr.c utilities/gcl.c utilities/utils_gcl.c

BSRCS = so_long_bonus.c key_hooks_bonus.c verify_map_bonus/check_map_bonus.c \
        verify_map_bonus/elements_check_bonus.c \
        utilities/ft_itoa.c utilities/ft_putstr_fd.c utilities/ft_split.c \
        utilities/ft_strdup.c utilities/ft_strjoin.c utilities/ft_strlcpy.c \
        utilities/ft_strlen.c utilities/ft_substr.c utilities/gcl.c utilities/utils_gcl.c

mlxFLAGS = -lmlx -framework OpenGL -framework AppKit 

NAME = so_long
BONUS_NAME = so_long_bonus

CC = cc
CFLAGS = -Wall -Wextra 

all: $(NAME)

$(NAME): $(SRCS) 
	$(CC) $(SRCS) $(mlxFLAGS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BSRCS) 
	$(CC) $(BSRCS) $(mlxFLAGS) -o $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
