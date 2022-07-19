/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/19 15:56:31 by spuustin         ###   ########.fr       */
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
/*
prints all files in a file-list. if -r is activated, the print is reversed.
*/
void	print_files_only(t_ls *b)
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
	print_files_only(b);
	ft_printf("\n");
	print_dir(b);	
}
