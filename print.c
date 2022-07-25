/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/25 15:56:55 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
sorts lists accordingly.
non-existing files aren't ever reversed	
*/

void	print_non_existings(t_ls *b)
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

	if (b->t == 1)
		sort_time(b->file_list);
	else
		sort_ascii(b->file_list);
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

void	print_dir_content(t_ls *b)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(b->path);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.') //needs better condition
			ft_printf("%s\n", dir->d_name);
	}
	closedir(d);
}

void	print_R(t_ls *b)
{
	int	i = 0;

	while (b->dir_list[i])
	{
		if (b->file_count != 0)
			write(1, "\n", 1);
		if (b->dir_count != 1 || (b->dir_count == 1 && b->file_count > 0))
			ft_printf("%s:\n", b->dir_list[i]);
		b->path = ft_strdup(b->dir_list[i]);
		list_files_in_dir(b, b->path);
		sort(b);
		print_files_only(b);
		initialize_list(b, 'f');
		i++;
		if (i < b->dir_count)
			write(1, "\n", 1);
			
	}
}

void	print_all(t_ls *b)
{
	print_non_existings(b);
	if (b->file_count > 0)
		print_files_only(b);
	if (b->dir_count > 0)
		print_R(b);
}

void	print(t_ls *b)
{
	if (b->l)
		print_long_format(b);
	else
		print_all(b);
	if (b->R == 1)
	{
		print_R(b);
	}
}
