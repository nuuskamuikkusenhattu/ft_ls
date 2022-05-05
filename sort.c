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

void	sort_alphabetically(t_flags *b)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < b->file_count - 1)
	{
		if (b->list[i][0] != '.')
		{
			//ft_printf("value between %s and %s is %d\n", b->list[i], b->list[i + 1], ft_strcmp(b->list[i], b->list[i + 1]));
			if (ft_strcmp(b->list[i], b->list[i + 1]) > 0)
			{
				temp = b->list[i];
				b->list[i] = b->list[i + 1];
				b->list[i + 1] = temp;
				i-= 2;
			}
		}
		i++;
	}
}

void	create_list(t_flags *b)
{
	int		i;
	struct dirent *dir;
	DIR		*d;
	i = 0;
	d = opendir("."); //probably send path as param
	while(i < b->file_count)
	{
		dir = readdir(d);
		b->list[i] = dir->d_name;
		i++;
	}
	closedir(d);
	b->list[i] = NULL;
}
