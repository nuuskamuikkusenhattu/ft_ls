# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 17:38:14 by spuustin          #+#    #+#              #
#    Updated: 2022/07/24 17:36:05 by spuustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ls
FLAGS= -Wall -Wextra -Werror
SRC= ft_ls.c parser.c list.c sort.c print.c long_format.c
TEST= test.c

all: $(NAME)

$(NAME) : 

# normaali compile saastamaan aikaa
test:
	gcc ${SRC} ${TEST} libft.a