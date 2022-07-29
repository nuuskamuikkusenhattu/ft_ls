/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/29 13:59:31 by spuustin         ###   ########.fr       */
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
	if (b->l)
	{
		printf("here i am, FC: %d\n", b->file_count);
		print_long_format(b);
	}
	else
	{
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
	int		i;

	i = 0;
	if (b->argc - b->flag_args == 1)
			list_files_in_dir(b, ".");
		if (b->file_count > 0)
		{
			print_files_only(b);
			write(1, "\n", 1);
		}
		initialize_list(b, 'f');
		list_sub_directories(b);
		if (b->argc - b->flag_args == 1)
			sort_ascii(b->dir_list);
	while (i < b->dir_count)
	{
		if (!(i == 0 && b->argc - b->flag_args == 2))
			ft_printf("%s:\n", b->dir_list[i]);
		b->path = ft_strdup(b->dir_list[i]);
		list_files_in_dir(b, b->path);
		//sort_ascii(b->file_list); //ei oo aina ascii, pitaa korjata sort()
		sort_list(b->file_list, b->sortc);
		print_files_only(b);
		initialize_list(b, 'f');
		i++;
		if (i != b->dir_count)
			write(1, "\n", 1);
	}
}

void	print_all_lists(t_ls *b)
{
	int	i = 0;

	print_non_existings(b);
	if (b->file_count > 0)
	{
		print_files_only(b);
		
	}
	while (b->dir_list[i])
	{
		b->path = ft_strjoin_three("",b->dir_list[i], "/");
		if (!b->path)
			exit(1);
		if (b->dirfileargc > 1)
			ft_printf("\n%s:\n", b->dir_list[i]);
		initialize_list(b, 'f');
		list_files_in_dir(b, b->dir_list[i]);
		print_files_only(b);
		i++;
	}
}

void	print(t_ls *b)
{
	if (b->R)
	{
		print_R(b);
	}
	else
	{
		print_all_lists(b);
	}
}
