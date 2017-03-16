# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/14 21:06:46 by pvan-erp          #+#    #+#              #
#    Updated: 2017/03/14 21:06:51 by pvan-erp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
SRC = main.c fdf.c points_from_file.c mlx_driver.c draw.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBDIR = -L./libft -L./minilibx_macos
LIBS = -lft -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re test asan


all: $(NAME)


$(NAME): $(SRC) libft/libft.a minilibx_macos/libmlx.a
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIBDIR) $(LIBS)
	
libft/libft.a:
	make -C ./libft

minilibx_macos/libmlx.a:
	make -C ./minilibx_macos

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx_macos/ clean

re: fclean all


test: $(SRC) libft/libft.a minilibx_macos/libmlx.a
	$(CC) alloc-wrap.c $(SRC) $(CFLAGS) $(LIBDIR) $(LIBS)
	./a.out "1 0"

asan: $(SRC) libft/libft.a minilibx_macos/libmlx.a
	$(CC) $(SRC) $(CFLAGS) $(LIBDIR) $(LIBS) -fsanitize=address
	./a.out ./test_maps/10-2.fdf
