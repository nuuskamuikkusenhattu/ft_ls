/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:23:32 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/18 13:52:57 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_link_helper(t_ls *b, char **argv, char *buf, int i)
{
	struct stat	temp;
	int			x;

	x = lstat(buf, &temp);
	if (S_ISDIR(temp.st_mode) == 1 && b->l == 0)
	{
		if (temp.st_mode & S_IRUSR || x == -1)
		{
			b->file_list[b->file_count] = ft_strdup(argv[i]);
			b->file_count++;
		}
		else
		{
			b->dir_list[b->dir_count] = ft_strdup(argv[i]);
			b->dir_count++;
		}
	}
	else
	{
		b->file_list[b->file_count] = ft_strdup(argv[i]);
		b->file_count++;
	}
}

void	add_to_dirlist(t_ls *b, char *name)
{
	b->dir_list[b->dir_count] = ft_strjoin("./", name);
	b->dir_count++;
	b->dir_list[b->dir_count] = NULL;
}

void	check_longest(t_ls *b, int len)
{
	if (len > b->longest_name)
		b->longest_name = len;
}

void	list_link(t_ls *b, char **argv, int i, int x)
{
	char		buf[MAX_PATH + 1];
	ssize_t		len;

	ft_bzero(buf, MAX_PATH + 1);
	len = readlink(argv[i], buf, MAX_PATH + 1);
	if (len != -1)
		list_link_helper(b, argv, buf, i);
}
