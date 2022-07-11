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

void	sort_alphabetically(char **list)
{
	int		i;
	char	*temp;

	i = 0;
	while (list[i] && list[i + 1])
	{
		if (ft_strcmp(list[i], list[i + 1]) > 0)
		{
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			i-= 2;
		}
		i++;
	}
}

void	reverse_sort(char **list)
{
	int		i;
	char	*temp;

	i = 0;
	while (list[i] && list[i + 1])
	{
		if (ft_strcmp(list[i], list[i + 1]) < 0)
		{
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			i-= 2;
		}
		i++;
	}
}

void	create_lists(char **argv, t_ls *b)
{
	int		i;
	int		exists;
	struct stat path;

	i = 1;
	while(argv[i])
	{
		exists = stat(argv[i], &path);
		if (exists == -1)
		{
			b->non_exists[b->ne_count] = ft_strnew(ft_strlen(argv[i]));
			if (!b->non_exists[b->ne_count])
				exit(1);
			b->non_exists[b->ne_count] = argv[i];
			b->ne_count++;
		}
		if (S_ISREG(path.st_mode) == 1 && exists != -1)
		{
			b->file_list[b->file_count] = ft_strnew(ft_strlen(argv[i]));
			if (!b->file_list[b->file_count])
				exit(1);
			b->file_list[b->file_count] = argv[i];
			b->file_count++;
		}
		if (S_ISDIR(path.st_mode) == 1 && exists != -1)
		{
			b->dir_list[b->dir_count] = ft_strnew(ft_strlen(argv[i]));
			if (!b->dir_list[b->dir_count])
				exit(1);
			b->dir_list[b->dir_count] = argv[i];
			b->dir_count++;
		}
		i++;
	}
	b->non_exists[b->ne_count] = NULL;
	// test_print_list(b, 'n'); //debug
	// test_print_list(b, 'f'); //debug
	// test_print_list(b, 'd'); //debug
}
