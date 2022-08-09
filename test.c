/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:28:49 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/09 18:10:18 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// prints a list with given char param (f,d,n)
void test_print_list(t_ls *b, char c)
{
	int i = 0;
	
	if (c == 'f')
	{
		printf("files are: \n");
		while(b->file_list[i])
		{
			printf("%s\n", b->file_list[i]);
			i++;
		}
	}
	if (c == 'd')
		printf("directories are: \n");
	{
		while(b->dir_list[i])
		{
			printf("%s\n", b->dir_list[i]);
			i++;
		}
		printf("<----LOB\n");
	}
	if (c == 'n')
	{
		printf("non-existing files are: \n");
		while(b->non_exists[i])
		{
			printf("%s\n", b->non_exists[i]);
			i++;
		}
	}
}

void	test_show_params(t_ls *b)
{
	if (b->a == 1)
		printf("a");
	if (b->l == 1)
		printf("l");
	if (b->t == 1)
		printf("t");
	if (b->r == 1)
		printf("r");
	if (b->R == 1)
		printf("R");
}
