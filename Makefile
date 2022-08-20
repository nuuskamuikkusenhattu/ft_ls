# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 17:38:14 by spuustin          #+#    #+#              #
#    Updated: 2022/08/18 16:05:55 by spuustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ls
FLAGS= #-Wall -Wextra -Werror
SRC= ft_ls.c parser.c list.c sort.c print.c long_format.c acl.c recursion.c \
long_format_helper.c list_helper.c print_helper.c

all: $(NAME)

$(NAME):
	make -C ./libft re
	gcc $(SRC) $(TEST) libft.a -o $(NAME)

clean:
	make -C ./libft clean
	rm -rf *.o
	rm -rf  libft/*.o

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

# normaali compile saastamaan aikaa
# test:
# 	gcc ${SRC} ${TEST} libft.a