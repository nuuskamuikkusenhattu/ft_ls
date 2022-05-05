/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/05/05 15:13:44 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_flags *b)
{
	int		i;

	ft_printf("size: %d\n", b->file_count);
	i = 0;
	while (i < b->file_count)
	{
		ft_printf("%s\n", b->list[i]);
		i++;
	}
}

static void	print_all(t_flags *b, char *path)
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

void	print_files(t_flags *b)
{
	b->a = 1;
	if (b->a == 1)
		print_all(b, ".");	
}
