/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/17 14:38:06 by spuustin         ###   ########.fr       */
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

	sort_ascii(b->non_exists);
	i = 0;
	while (b->non_exists[i])
	{
		if (ft_strlen(b->non_exists[i]) > 255)
			ft_printf("ft_ls: %s: File name too long\n", b->non_exists[i]);
		else
			ft_printf("ft_ls: %s: No such file or directory\n", b->non_exists[i]);
		i++;
	}
}

void	print_with_serial_nro(t_ls *b)
{
	struct stat info;
	int i = 0;
	char *file_path;
	
	while(b->file_list[i])
	{
		file_path = ft_strjoin(b->path, b->file_list[i]);
		lstat(file_path, &info);
		ft_printf("%d %s\n", info.st_ino, b->file_list[i]);
		i++;
	}
}
/*
prints all files in a file-list. if -r is activated, the print is reversed.
*/
void	print_files_only(t_ls *b)
{
	int		i;
	int		j;
	struct winsize window;
	int columns;
	int rows;
	int total = 0;
	ioctl(0, TIOCGWINSZ, &window);
	columns = window.ws_col / (b->longest_name + 1);
	if (columns < 1)
		columns = 1;
	rows = b->file_count / columns;
	if (columns * rows != b->file_count)
		rows++;
	i = 0;
	j = 0;
	sort_list(b->file_list, b->sortc, b->r, b->path);
	if (b->l)
		print_long_format(b, 0, 0);
	else if (b->option_i)
		print_with_serial_nro(b);
	else
	{
		while (total < b->file_count)
		{
			if (b->file_list[i + j])
			{
				ft_printf("%-*s", b->longest_name + 1, b->file_list[i + j]);
				total++;	
			}
			j += rows;
			if ((j >= (rows * columns)) || total == b->file_count)
			{
				j = 0;
				i++;
				write(1, "\n", 1);
			}
		}
	}
	b->longest_name = 0;
}

void	print_all_lists(t_ls *b)
{
	int	i = 0;
	char *current;

	print_non_existings(b);
	if (b->dirfileargc == 0 && b->l)
		get_total(b);
	if (b->file_count > 0)
		print_files_only(b);
	if (b->file_count > 0 && b->dir_list[i])
		write(1, "\n", 1);
	sort_list(b->dir_list, b->sortc, b->r, b->path);
	while (b->dir_list[i])
	{
		if (b->dir_list[i][ft_strlen(b->dir_list[i]) - 1] == '/')
			b->path = ft_strdup(b->dir_list[i]);
		else
		{
			current = ft_strjoin(b->dir_list[i], "/");
			b->path = ft_strdup(current);
			free(current);
		}
		if (!b->path)
			exit(1);
		if (b->dirfileargc > 1)
			ft_printf("%s:\n", b->dir_list[i]);
		initialize_list(b, 'f');
		list_files_in_dir(b, b->dir_list[i]);
		if (b->l)
			get_total(b);
		print_files_only(b);
		if (i != b->dir_count - 1)
			write(1, "\n", 1);
		i++;
		free(b->path);
	}
}

char **recursion_dir_list(char *path)
{
	DIR *d;
	struct dirent *dir;
	char **ret;
	int i = 0;

	d = opendir(path);
	ret = (char **)malloc(sizeof(char *) * 1000); //optimize
	if (!ret)
		exit (1);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type == 4 && dir->d_name[0] != '.')
			{
				ret[i] = ft_strjoin(path, dir->d_name); 
				if (!ret[i])
					exit(1);
				i++;
			}
		}
	closedir(d);
	}
	ret[i] = NULL;
	return (ret);
}

void	recursion(t_ls *b, char *path)
{
	char *current;
	char **d;
	int i = 0;

	b->ne_count = -1;
	d = recursion_dir_list(path);
	sort_list(d, b->sortc, b->r, "");
	while (d[i])
	{
		write(1, "\n", 1);
		ft_printf("%s:\n", d[i]);
		current = ft_strjoin(d[i], "/");
		initialize_list(b, 'f');
		list_files_in_dir(b, current);
		print_files_only(b);
		recursion(b, current);
		free(current);
		i++;
	}
	ft_free_array(d);
}

void	print(t_ls *b)
{
	if (b->R)
	{
		print_non_existings(b);
		b->ne_count = -1;
		print_files_only(b);
		if (b->dir_count > 0 && b->file_count > 0)
			write(1, "\n", 1);
		int i = 0;
		while (b->dir_list[i])
		{
			b->path = ft_strjoin(b->dir_list[i], "/");
			if (i != 0 || (i == 0 && b->file_count > 0) || b->dir_count > 1)
				ft_printf("%s:\n", b->path);
			initialize_list(b, 'f');
			list_files_in_dir(b, b->path);
			if (b->l)
				get_total(b);
			print_files_only(b);
			recursion(b, b->path);
			i++;
			free(b->path);
			if (b->dir_list[i])
				write(1, "\n", 1);
		}
	}
	else
		print_all_lists(b);
}
