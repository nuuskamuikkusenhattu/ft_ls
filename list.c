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

/*
lists all files in a directory with a given path
*/
void	list_all_in_current_dir(t_ls *b, char *path)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			b->file_list[b->file_count] = ft_strdup(dir->d_name);
			if (!b->file_list[b->file_count])
				exit(1);
			b->file_count++;
		}
		closedir(d);
	}
}

void	list_non_hidden(t_ls *b, char *path)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] != '.')
			{
				b->file_list[b->file_count] = ft_strdup(dir->d_name);
				if (!b->file_list[b->file_count])
					exit(1);
				b->file_count++;
			}
		}
		b->file_list[b->file_count] = NULL;
	}
	closedir(d);
}

void	list_directories_only(t_ls *b)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(b->path);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_type == 4 && dir->d_name[0] != '.')
		{
			b->dir_list[b->dir_count] = ft_strjoin(b->path, dir->d_name);
			if (!b->dir_list[b->dir_count])
				exit(1);
			b->dir_count++;
		}
	}
}
// might be totally useless function in its entiry
void	create_lists(char **argv, t_ls *b)
{
	int		i;
	int		exists;
	struct stat path;

	i = 1 + b->flag_args;
	while(argv[i])
	{
		exists = stat(argv[i], &path);
		if (exists == -1)
		{
			b->non_exists[b->ne_count] = ft_strdup(argv[i]);
			if (!b->non_exists[b->ne_count])
				exit(1);
			b->non_exists[b->ne_count] = argv[i];
			b->ne_count++;
		}
		if (S_ISREG(path.st_mode) == 1 && exists != -1)
		{
			b->file_list[b->file_count] = ft_strdup(argv[i]);
			if (!b->file_list[b->file_count])
				exit(1);
			b->file_count++;
		}
		if (S_ISDIR(path.st_mode) == 1 && exists != -1)
		{
			b->dir_list[b->dir_count] = ft_strdup(argv[i]);
			if (!b->dir_list[b->dir_count])
				exit(1);
			b->dir_list[b->dir_count] = argv[i];
			b->dir_count++;
		}
		i++;
	}
	b->non_exists[b->ne_count] = NULL;
	b->file_list[b->file_count] = NULL;
	b->dir_list[b->dir_count] = NULL;
	// test_print_list(b, 'n'); //debug
	// test_print_list(b, 'f'); //debug
	// test_print_list(b, 'd'); //debug
}
