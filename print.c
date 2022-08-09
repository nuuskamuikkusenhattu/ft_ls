/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/09 17:30:41 by spuustin         ###   ########.fr       */
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
			ft_printf("ls: %s: File name too long\n", b->non_exists[i]);
		else
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
		sort_list(b->file_list, b->sortc, b->file_count);
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
			sort_list(b->dir_list, b->sortc, b->dir_count);
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
		sort_list(b->dir_list, b->sortc, b->dir_count);
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
		print_files_only(b);
	if (b->file_count > 0 && b->dir_list[i])
		write(1, "\n", 1);
	if (b->r && b->t)
		sort_rt(b);
	else
		sort_list(b->dir_list, b->sortc, b->dir_count);
	while (b->dir_list[i])
	{
		if (b->dir_list[i][ft_strlen(b->dir_list[i]) - 1] == '/')
			b->path = b->dir_list[i];
		else
			b->path = ft_strjoin_three("",b->dir_list[i], "/");
		if (!b->path)
			exit(1);
		if (b->dirfileargc > 1)
			ft_printf("%s:\n", b->dir_list[i]);
		initialize_list(b, 'f');
		list_files_in_dir(b, b->dir_list[i]);
		print_files_only(b);
		if (i != b->dir_count - 1)
			write(1, "\n", 1);
		i++;
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
	//protect
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
	// else
	// 	ft_printf("opendir failed in print.c recursion_dir_list\n");
	ret[i] = NULL;
	return (ret);
}

void	recursion(t_ls *b, char *path)
{
	char *current;
	char **d;
	int i = 0;
	//test_print_list(b, 'd');
	//ft_printf("dirs contains: ");
	// while(dirs[n])
	// {
	// 	ft_printf("%s, ", dirs[n]);
	// 	n++;
	// }
	d = recursion_dir_list(path);
	sort_list(d, b->sortc, b->r);
	while (d[i])
	{
		current = ft_strjoin(d[i], "/");
		ft_printf("path is %s\n", current);
		recursion(b, ft_strdup(current));
		i++;
	}
	free(current);
	// list_sub_directories(b);
	// test_print_list(b, 'd');
	
	// tassa vaiheessa alkup. kansion kansiot on listattu ja jarjestetty.
	// nyt pitaa kutsua jokaiselle funktiota list directories only, ja kutsua sita uudelleen niin kauan, kun se palauttaa >0
}

void	print(t_ls *b)
{
	if (b->R)
	{
		print_non_existings(b);
		print_files_only(b);
		int i = 0;
		char *path;
		while (b->dir_list[i])
		{
			path = ft_strjoin_three("./", b->dir_list[i], "/");
			if (b->dir_count >1)
				ft_printf("%s\n", path);
			recursion(b, path);
			i++;	
			free(path);
		}
	}
	else
	{
		print_all_lists(b);
	}
}
