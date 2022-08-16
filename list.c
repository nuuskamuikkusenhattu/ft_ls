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

void	permission_denied_error(char *str)
{
	int i;
	int errno = 0;
	int ends_with_slash = 0;
	i = ft_strlen(str) -1;
	if (str[i] == '/')
		ends_with_slash = 1;
	if (errno == 0)
	{
		while (str[i] == '/')
		{
			str[i] = '\0';
			i--;
		}
		while(i > 0)
		{
			if (str[i] == '/')
				break;
			i--;
		}
		if (i != 0)
			ft_printf("ft_ls: %s: Permission denied\n", str + i + 1);
		else if (i == 0 && ends_with_slash == 1)
			ft_printf("ft_ls: : Permission denied\n");
		else
			ft_printf("ft_ls: %s: Permission denied\n", str + i);
	}
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
				if (b->R == 1 && dir->d_type == 4 && b->ne_count != -1)
				{
					b->dir_list[b->dir_count] = ft_strjoin("./", dir->d_name);
					b->dir_count++;
				}
				if (!b->file_list[b->file_count])
					exit(1);
				b->file_count++;
				if (dir->d_namlen > b->longest_name)
					b->longest_name = dir->d_namlen;
			}
		}
		b->file_list[b->file_count] = NULL;
		closedir(d);
	}
	else
	{
		permission_denied_error(path);
		//irrota tiedoston nimi pathista
		//tulosta pelkka se
		//jos pathissa on kaks perattaista //, tulosta pelkka vali
		// if (path[ft_strlen(path) - 1] == '/') //this needs a condition
		// 	ft_printf("ft_ls: : Permission denied\n");
		// else if (path[0] == '.' && path[1] == '/' && path[2])
		// 	ft_printf("ft_ls: %s: Permission denied\n", path + 2); //this aint right
		// else
		// 	ft_printf("ft_ls: %s: Permission denied\n", path);
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
	b->dir_list[b->dir_count] = NULL;
}

void	list_from_argv(char **argv, t_ls *b)
{
	int		i;
	int		exists;
	struct stat path;
	int nameLen = 0;

	i = 1 + b->flag_args;
	while(argv[i])
	{
		nameLen = ft_strlen(argv[i]);
		exists = lstat(argv[i], &path);
		if (exists == -1)
		{
			b->non_exists[b->ne_count] = ft_strdup(argv[i]);
			if (!b->non_exists[b->ne_count])
				exit(1);
			b->ne_count++;
		}
		else
		{
			if (nameLen > b->longest_name)
				b->longest_name = nameLen;
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
	sort_ascii(b->dir_list);
}

void	create_lists(char **argv, int argc, t_ls *b)
{
	if (b->dirfileargc == 0)
		list_files_in_dir(b, b->path);
	else
		list_from_argv(argv, b);
}
