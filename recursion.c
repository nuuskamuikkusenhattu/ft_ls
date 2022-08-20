/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:04:32 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/20 20:33:14 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	count_dirs(t_ls *b, char *path)
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
			if (dir->d_type == 4 && (b->a == 1 || (b->a == 0 && dir->d_name[0] \
			!= '.')))
				count++;
		}
		closedir(d);
	}
	return (count);
}

char	**fill_list(t_ls *b, struct dirent *dir, DIR *d, char *path)
{
	int		i;
	char	**ret;
	int		count;

	i = 0;
	count = count_dirs(b, path) + 1;
	ret = (char **)malloc(sizeof(char *) * count);
	if (!ret)
		exit (1);
	while (1)
	{
		dir = readdir(d);
		if (dir == NULL)
			break ;
		if (dir->d_type == 4 && (b->a == 1 || (b->a == 0 && dir->d_name[0] \
		!= '.')))
		{
			if (!(dir->d_name[1] == '.' || (dir->d_name[0] == '.' && \
			!dir->d_name[1])))
				ret[i++] = ft_strjoin(path, dir->d_name);
		}
	}
	ret[i] = NULL;
	return (ret);
}

char	**recursion_dir_list(t_ls *b, char *path, char **ret)
{
	DIR				*d;
	struct dirent	*dir;

	dir = NULL;
	d = opendir(path);
	if (d)
	{
		ret = fill_list(b, dir, d, path);
		closedir(d);
	}
	else
	{
		ret = (char **)malloc(sizeof(char *) * 1);
		if (!ret)
			exit(1);
		ret[0] = NULL;
	}
	return (ret);
}

void	recursion(t_ls *b, char *path, int i, char **d)
{
	char	*current;

	b->ne_count = -1;
	d = recursion_dir_list(b, path, NULL);
	sort_list(d, b->sortc, b->r, "");
	while (d[i])
	{
		write(1, "\n", 1);
		ft_printf("%s:\n", d[i]);
		current = ft_strjoin(d[i], "/");
		recursion_helper(b, current);
		ft_memdel((void *)&b->path);
		recursion(b, current, 0, NULL);
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
	if (b->file_count > 0)
		ft_free_array(b->file_list);
	else
		free(b->file_list);
	count_all(b, b->path);
	init_list(b, 'f', b->file_count + 1);
	b->file_count = 0;
	list_files_in_dir(b, b->path);
	print_files_only(b);
	recursion(b, b->path, 0, NULL);
}
