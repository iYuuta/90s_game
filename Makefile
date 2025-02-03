SRCS = mandatory/so_long.c mandatory/key_hooks.c mandatory/check_map.c mandatory/elements_check.c
BSRCS = bonus/so_long_bonus.c bonus/key_hooks_bonus.c bonus/check_map_bonus.c bonus/elements_check_bonus.c

UTILS = utilities/ft_itoa.c utilities/ft_putstr_fd.c utilities/ft_split.c utilities/ft_strdup.c utilities/ft_strjoin.c \
        utilities/ft_strlcpy.c utilities/ft_strlen.c utilities/ft_substr.c utilities/gcl.c utilities/utils_gcl.c

UOBJS = $(UTILS:.c=.o)
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = so_long
BONUS_NAME = so_long_bonus

mlxFLAGS = -lXext -lX11 -lm


all: $(NAME)

$(NAME): $(OBJS) $(UOBJS)
	$(CC) $(OBJS) $(UOBJS) minilibx-linux/libmlx.a $(mlxFLAGS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BOBJS) $(UOBJS)
	$(CC) $(BOBJS) $(UOBJS) minilibx-linux/libmlx.a $(mlxFLAGS) -o $(BONUS_NAME)

mandatory/%.o: mandatory/%.c mandatory/so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/so_long_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

utilities/%.o: utilities/%.c utilities/so_long_utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS) $(UOBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
