/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/12 19:13:06 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
sorts lists accordingly.
non-existing files aren't ever reversed	
*/

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
	if (b->r == 0)
	{
		while (b->file_list[i])
		{
			ft_printf("%s\n", b->file_list[i]);
			i++;
		}
	}
	else
	{
		i = b->file_count;
		while(i > 0)
		{
			ft_printf("%s\n", b->file_list[i - 1]);
			i--;
		}
	}
}

static void	print_dir(t_ls *b)
{
	b = NULL;
}

void	print_all(t_ls *b)
{
	sort(b);
	print_non_existings(b);
	print_files(b);
	ft_printf("\n");
	print_dir(b);	
}
