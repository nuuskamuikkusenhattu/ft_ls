/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:28:49 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/11 17:49:36 by spuustin         ###   ########.fr       */
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
