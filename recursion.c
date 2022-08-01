/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:29:18 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/01 13:58:33 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_for_R(t_ls *b)
{
	int i = 0;
	
	while (b->dir_list[i])
	{
		ft_printf("%s:\n", b->dir_list[i]);
		initialize_list(b, 'f');
		b->path = ft_strdup(b->dir_list[i]);
		//protect
		list_files_in_dir(b, b->path);
		print_files_only(b);
		i++;
		write(1, "\n", 1);
	}
}

void	R_start(t_ls *b)
{
	char **dirs;
	int i = 0;
	
	dirs = (char **)malloc(sizeof (char *) * b->dir_count + 1);
	//protect
	//printf("dircount when we start: %d\n", b->dir_count);
	while (b->dir_list[i])
	{
		dirs[i] = ft_strdup(b->dir_list[i]);
		//protect
		i++;
	}
	dirs[i] = NULL;
	//printf("%d %d\n", b->dir_count, i);
	// i = 0;
	// while (dirs[i])
	// {
	// 	printf("%s\n", dirs[i]);
	// 	i++;
	// }
	i = 0;
	while (dirs[i])
	{
		initialize_list(b, 'd');
		b->dir_list[0] = ft_strdup(dirs[i]);
		b->dir_count = 1;
		//protect
		//printf("%s\n", b->dir_list[0]);
		list_sub_directories(b);
		sort_list(b->dir_list, b->sortc);
		//test_print_list(b, 'd');
		print_for_R(b);
		i++;
	}
	exit(0);
}
