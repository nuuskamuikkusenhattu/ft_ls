/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:29:42 by spuustin          #+#    #+#             */
/*   Updated: 2022/05/05 14:33:21 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_alphabetically(t_ls *b)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < b->file_count - 1)
	{
		if (b->file_list[i][0] != '.')
		{
			//ft_printf("value between %s and %s is %d\n", b->file_list[i], b->file_list[i + 1], ft_strcmp(b->file_list[i], b->file_list[i + 1]));
			if (ft_strcmp(b->file_list[i], b->file_list[i + 1]) > 0)
			{
				temp = b->file_list[i];
				b->file_list[i] = b->file_list[i + 1];
				b->file_list[i + 1] = temp;
				i-= 2;
			}
		}
		i++;
	}
}

void	create_lists(t_ls *b)
{
	int		i;
	struct dirent *dir;
	struct stat path;
	DIR		*d;

	i = 0;
	d = opendir("."); //probably send path as param
	while((dir = readdir(d)) != NULL)
	{
		printf("%s\n", dir->d_name);
		printf("type %d\n", stat(dir->d_name, &path));
	}
	closedir(d);
	b = NULL;
}
