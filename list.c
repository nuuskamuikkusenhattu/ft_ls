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

void	list_files_in_dir(t_ls *b, char *path)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(path);
	if (d)
	{
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			if (b->a == 1 || (b->a == 0 && dir->d_name[0] != '.'))
			{
				b->file_list[b->file_count] = ft_strdup(dir->d_name);
				if (b->capital_r == 1 && dir->d_type == 4 && b->ne_count != -1)
					add_to_dirlist(b, dir->d_name);
				b->file_count++;
				check_longest(b, dir->d_namlen);
			}
		}
		b->file_list[b->file_count] = NULL;
		closedir(d);
	}
	else
		permission_denied_error(path, b);
}

void	list_from_argv(char **argv, t_ls *b, int i)
{
	struct stat	path;

	i = 1 + b->flag_args;
	while (argv[i])
	{
		b->name_len = ft_strlen(argv[i]);
		b->exists = lstat(argv[i], &path);
		list_file(b, path, argv, i);
		i++;
	}
	b->non_exists[b->ne_count] = NULL;
	b->file_list[b->file_count] = NULL;
	b->dir_list[b->dir_count] = NULL;
}

void	count_helper(t_ls *b, DIR *d)
{
	struct dirent	*dir;

	while (1)
	{
		dir = readdir(d);
		if (dir == NULL)
			break ;
		if (dir->d_type == 4 && (b->a == 1 || (b->a == 0 && dir->d_name[0] \
		!= '.')))
		{
			b->file_count++;
			b->dir_count++;
		}
		else
		{
			b->file_count++;
		}
	}
}

void	count_all(t_ls *b, char *path)
{
	DIR				*d;

	d = opendir(path);
	if (d)
	{
		count_helper(b, d);
		closedir(d);
	}
	else
	{
		b->dir_count++;
		b->file_count++;
	}
}

void	create_lists(char **argv, t_ls *b)
{
	if (b->dirfileargc == 0)
	{
		count_all(b, b->path);
		init_list(b, 'd', b->dir_count + 1);
		init_list(b, 'f', b->file_count + 1);
		b->file_count = 0;
		b->dir_count = 0;
		list_files_in_dir(b, b->path);
	}
	else
	{
		init_list(b, 'n', b->dirfileargc + 1);
		init_list(b, 'd', b->dirfileargc + 1);
		init_list(b, 'f', b->dirfileargc + 1);
		list_from_argv(argv, b, 0);
	}
}
