/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/11 19:54:10 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
sorts lists accordingly.
non-existing files aren't ever reversed	
*/
static void	sort(t_ls *b)
{
	if (b->r == 0)
	{
		sort_alphabetically(b->non_exists);
		sort_alphabetically(b->file_list);
		sort_alphabetically(b->dir_list);
	}
	else
	{
		reverse_sort(b->file_list);
		reverse_sort(b->dir_list);
	}
}

static void	print_non_existings(t_ls *b)
{
	int		i;

	i = 0;
	while (b->non_exists[i])
	{
		ft_printf("ls: %s: No such file or directory\n", b->non_exists[i]);
		i++;
	}
}

static void	print_files(t_ls *b)
{
	int		i;

	i = 0;
	while (b->file_list[i])
	{
		ft_printf("%s\n", b->file_list[i]);
		i++;
	}
}

static void	print_dir(t_ls *b)
{
	b = NULL;
}

void	print_all(t_ls *b)
{
	sort(b);
	if (b->ne_count > 0)
	{
		print_non_existings(b);
	}
	if (b->file_count > 0)
	{
		print_files(b);
	}
	if (b->dir_count > 0)
	{
		ft_printf("\n");
		print_dir(b);
	}
}
