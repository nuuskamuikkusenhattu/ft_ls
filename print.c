/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/11 14:56:23 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_ls *b)
{
	int		i;

	ft_printf("size: %d\n", b->file_count);
	i = 0;
	while (i < b->file_count)
	{
		ft_printf("%s\n", b->file_list[i]);
		i++;
	}
}

static void	print_all(t_ls *b, char *path)
{
	struct 	dirent *dir;
	DIR 	*d;
	int		c;

	c = 0;
	d = opendir(path);
	while (c < b->file_count)
	{
		dir = readdir(d);
		printf("%s\n", dir->d_name);
		c++;
	}
}

void	print_files(t_ls *b)
{
	b->a = 1;
	if (b->a == 1)
		print_all(b, ".");	
}
