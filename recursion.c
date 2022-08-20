/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:04:32 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/20 15:59:30 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	count_dirs(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				count;

	count = 0;
	d = opendir(path);
	if (d)
	{
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			if (dir->d_type == 4 && dir->d_name[0] != '.')
				count++;
		}
		closedir(d);
	}
	return (count);
}

char	**recursion_dir_list(char *path, int i, int count, char **ret)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(path);
	count = count_dirs(path) + 1;
	ret = (char **)malloc(sizeof(char *) * count);
	if (!ret)
		exit (1);
	if (d)
	{
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			if (dir->d_type == 4 && dir->d_name[0] != '.')
			{
				ret[i] = ft_strjoin(path, dir->d_name);
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
	char	*current;
	char	**d;
	int		i;

	i = 0;
	b->ne_count = -1;
	d = recursion_dir_list(path, 0, 0, NULL);
	sort_list(d, b->sortc, b->r, "");
	while (d[i])
	{
		write(1, "\n", 1);
		ft_printf("%s:\n", d[i]);
		current = ft_strjoin(d[i], "/");
		//initialize_list(b, 'f');
		if (b->file_count > 0)
			ft_free_array(b->file_list);
		else
		{
			free(b->file_list);
			b->file_list = NULL;
		}
		count_all(b, current);
		init_list(b, 'f', b->file_count + 1);
		b->file_count = 0;
		list_files_in_dir(b, current);
		free(b->path);
		b->path = ft_strdup(current);
		// ft_printf("recursion.c/recursion: current is %s\n", current);
		// ft_printf("recursion.c/recursion: path is %s\n", b->path);
		print_files_only(b);
		free(b->path);
		b->path = NULL;	
		recursion(b, current);
		free(current);
		i++;
	}
	if (d[0])
		ft_free_array(d);
	else
		free(d);
}

void	print_all_dirs(t_ls *b, int i)
{
	b->path = ft_strjoin(b->dir_list[i], "/");
	if (i != 0 || (i == 0 && b->file_count > 0) || b->dir_count > 1)
		ft_printf("%s:\n", b->dir_list[i]);
	//initialize_list(b, 'f');
	if (b->file_count > 0)
		ft_free_array(b->file_list);
	else
		free(b->file_list);
	//ft_printf("recursion.c: path on %s\n", b->path);
	count_all(b, b->path);
	init_list(b, 'f', b->file_count + 1);
	b->file_count = 0;
	list_files_in_dir(b, b->path);
	// if (b->l && (b->file_count != 0 || b->dirfileargc == 0))
	// {
	// 	ft_printf("get_total kutsu tuli recursion.c:sta\n");
	// 	get_total(b);
	// }
	print_files_only(b);
	recursion(b, b->path);
}
