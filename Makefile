# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 17:38:14 by spuustin          #+#    #+#              #
#    Updated: 2022/07/12 19:02:46 by spuustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ls
FLAGS= -Wall -Wextra -Werror
SRC= ft_ls.c parser.c create_list.c sort.c print.c
TEST= test.c

all: $(NAME)

$(NAME) : 

# normaali compile saastamaan aikaa
test:
	gcc ${FLAGS} ${SRC} ${TEST} libft.a