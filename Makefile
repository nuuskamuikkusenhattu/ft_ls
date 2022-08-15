# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 17:38:14 by spuustin          #+#    #+#              #
#    Updated: 2022/08/15 15:38:43 by spuustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ls
FLAGS= -Wall -Wextra -Werror
SRC= ft_ls.c parser.c list.c sort.c print.c long_format.c acl.c
TEST= test.c recursion.c

all: $(NAME)

$(NAME) : 

# normaali compile saastamaan aikaa
test:
	gcc ${SRC} ${TEST} libft.a