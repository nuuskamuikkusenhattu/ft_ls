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

void	list_sub_directories(t_ls *b)
{
	int i = 0;
	while(i < b->dir_count)
	{
		b->path = ft_strjoin(b->dir_list[i], "/"); //this may need a condition
		//printf("current path is %s\n", b->path);
		list_directories_only(b);
		i++;
	}
	b->dir_list[b->dir_count] = NULL;
}

void	list_files_in_dir(t_ls *b, char *path)
{
	DIR *d;
	struct dirent *dir;
	int	total;

	total = 0;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (b->a == 1 || (b->a == 0 && dir->d_name[0] != '.'))
			{
				b->file_list[b->file_count] = ft_strdup(dir->d_name);
				if (b->R && dir->d_type == 4 && b->ne_count != -1 && b->R == 0)
				{
					b->dir_list[b->dir_count] = ft_strjoin("./", dir->d_name);
					//protect
					b->dir_count++;
				}
				if (!b->file_list[b->file_count])
				{
					printf("exiting, bye\n"); //debug
					exit(1);
				}
				b->file_count++;
			}
		}
		b->file_list[b->file_count] = NULL;
		closedir(d);
	}
	else
	{
		if (path[0] == '.' && path[1] == '/' && path[2])
			ft_printf("ls: %s: Permission denied\n", path + 2);
		else
			ft_printf("ls: %s: Permission denied\n", path);
	}
}

void	list_directories_only(t_ls *b)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(b->path);
	if (d)
	{
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
	closedir(d);
	}
	else
		ft_printf("opendir failed in list.c\n");
	b->dir_list[b->dir_count] = NULL;
}

void	list_from_argv(char **argv, t_ls *b)
{
	int		i;
	int		exists;
	struct stat path;

	i = 1 + b->flag_args;
	while(argv[i])
	{
		exists = lstat(argv[i], &path);
		if (exists == -1)
		{
			b->non_exists[b->ne_count] = ft_strdup(argv[i]);
			if (!b->non_exists[b->ne_count])
				exit(1);
			b->ne_count++;
		}
		if (S_ISLNK(path.st_mode) == 1)
		{
			char buf[MAX_PATH + 1];
			ssize_t len;
			int x;

			ft_bzero(buf, MAX_PATH + 1);
			len = readlink(argv[i], buf, MAX_PATH + 1);
			if (len != -1)
			{
				struct stat temp;
				x = lstat(buf, &temp);
				if (S_ISDIR(temp.st_mode) == 1 && b->l == 0)
				{
					if (temp.st_mode & S_IRUSR || x == -1)
					{
						b->file_list[b->file_count] = ft_strdup(argv[i]);
						if (!b->file_list[b->file_count])
							exit(1);
						b->file_count++;
					}
					else
					{
						b->dir_list[b->dir_count] = ft_strdup(argv[i]);
						if (!b->dir_list[b->dir_count])
							exit(1);
						b->dir_count++;
					}
				}
				else
				{
					b->file_list[b->file_count] = ft_strdup(argv[i]);
					if (!b->file_list[b->file_count])
						exit(1);
					b->file_count++;
				}
			}
			//jos kohde on kansio JA siihen ei ole oikeuksia, ala laita listaan
			// vaan laita kohdekansio kansiolistaan
		}
		if (S_ISREG(path.st_mode) == 1 && S_ISLNK(path.st_mode) == 0)
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
			b->dir_count++;
		}
		i++;
	}
	b->non_exists[b->ne_count] = NULL;
	b->file_list[b->file_count] = NULL;
	b->dir_list[b->dir_count] = NULL;
	//ft_printf("dircount %d, fcount %d, necount %d\n", b->dir_count, b->file_count, b->ne_count); //debug
	sort_ascii(b->dir_list);
}

void	create_lists(char **argv, int argc, t_ls *b)
{
	if (b->dirfileargc == 0)
		list_files_in_dir(b, b->path);
	else
		list_from_argv(argv, b);
}
