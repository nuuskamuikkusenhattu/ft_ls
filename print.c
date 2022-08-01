/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/29 20:19:32 by spuustin         ###   ########.fr       */
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
		print_long_format(b);
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

void	print_dirlist(t_ls *b)
{
	int i = 0;
	while (b->dir_list[i])
	{
		b->path = ft_strdup(b->dir_list[i]);
		list_files_in_dir(b, b->path);
		sort_list(b->file_list, b->sortc);
		ft_printf("%s:\n", b->dir_list[i]);
		print_files_only(b);
		if (i < b->dir_count - 1)
			write(1, "\n", 1);
		initialize_list(b, 'f');
		i++;
	}
}

void	print_R(t_ls *b)
{
	int		i;
	int c = 0;
	char **temp;

	temp = (char **)malloc(sizeof(char *) * b->dir_count);
	if (!temp)
		exit(1);
	i = 0;
	if (b->argc - b->flag_args == 1)
			list_files_in_dir(b, ".");
		if (b->file_count > 0)
		{
			print_files_only(b);
			write(1, "\n", 1);
		}
		initialize_list(b, 'f');
		//list_sub_directories(b);
		if (b->argc - b->flag_args == 1) //why this condition
			sort_list(b->dir_list, b->sortc);
	while (b->dir_list[i])
	{
		temp[i] = ft_strdup(b->dir_list[i]);
		if(!temp[i])
			exit(1);
		i++;
	}
	temp[i] = NULL;
	c = b->dir_count;
	i = 0;
	while (i < c)
	{
		initialize_list(b, 'd');
		b->dir_list[0] = ft_strdup(temp[i]);
		b->dir_count = 1;
		//protect
		//printf("first on the list is %s\n", b->dir_list[0]); //debug
		list_sub_directories(b);
		// if (!(i == 0 && b->argc - b->flag_args == 2)) //joku ehto tassa taytyy olla kylla
		// 	ft_printf("%s:\n", b->dir_list[i]);
		sort_list(b->dir_list, b->sortc);
		print_dirlist(b);
		i++;
		if (i != c)
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
