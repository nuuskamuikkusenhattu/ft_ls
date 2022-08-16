/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:58:56 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/16 16:32:35 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_ascii(char **list)
{
	int		i;
	char	*temp;

	i = 0;
	while (list[i] && list[i + 1])
	{
		if (ft_strcmp(list[i], list[i + 1]) > 0)
		{
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			i-=2;
		}
		i++;
		if (i < 0)
			i = 0;
	}
}

void	reverse_ascii(char **list)
{
	int		i;
	char	*temp;

	i = 0;
	while (list[i] && list[i + 1])
	{
		if (ft_strcmp(list[i], list[i + 1]) < 0)
		{
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			i-=2;
		}
		i++;
		if (i < 0)
			i = 0;
	}
}

void	sort_by_time(char **list, char *path)
{
	int		i;
	char	*temp;
	struct stat f_status;
	long long	this_time[2];
	long long	next_time[2];
	char *current;

	sort_ascii(list);
	i = 0;
	//ft_printf("path is %s\n", path);
	while (list[i] && list[i + 1])
	{
		current = ft_strjoin(path, list[i]);
		lstat(current, &f_status);
		//ft_printf("current_path is %s\n", current);
		this_time[0] = f_status.st_mtime;
		this_time[1] = f_status.st_mtimespec.tv_nsec;
		free(current);
		current = ft_strjoin(path, list[i + 1]);
		lstat(current, &f_status);
		//ft_printf("current_path is %s\n", current);
		free(current);
		next_time[0] = f_status.st_mtime;
		next_time[1] = f_status.st_mtimespec.tv_nsec;
		//ft_printf("time of %s is  %lld, time of %s is  %lld\n", list[i], this_time, list[i + 1], next_time); //debug
		if (this_time[0] < next_time[0] || (this_time[0] == next_time[0] && this_time[1] < next_time[1]))
		{
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			i-=3;
		}
		i++;
		if (i < 0)
			i = 0;
	}
}

/*
	orders files by modification time
*/
void	sort_time(char **list)
{
	int		i;
	char	*temp;
	struct stat f_status;
	long long	this_time;
	long long	next_time;

	sort_ascii(list);
	i = 0;
	while (list[i] && list[i + 1])
	{
		lstat(list[i], &f_status);
		this_time = f_status.st_mtime;
		lstat(list[i + 1], &f_status);
		next_time = f_status.st_mtime;
		//ft_printf("time of %s is  %lld, time of %s is  %lld, %d%d\n", list[i], this_time, list[i + 1], next_time, x, y); //debug
		if (this_time < next_time)
		{
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			i-=3;
		}
		i++;
		if (i < 0)
			i = 0;
	}
}

/*
if -rt, then dirs need to be sortet first with -t (subdir sensitive)
and then reversed (subdir sensitive)
*/

void	sort_rt(t_ls *b)
{
	sort_list(b->dir_list, 't', b->r, b->path);
	//reverse the gotten list
	int c = b->dir_count - 1;
	int i = 0;
	char *temp;
	while (i < c)
	{
		temp = b->dir_list[c];
		b->dir_list[c] = b->dir_list[i];
		b->dir_list[i] = temp;
		i++;
		c--;
	}
	int n = 1;
	i = 0;
	while (b->dir_list[i + 1])
	{
		if (is_subdir_substr(b->dir_list[i + 1], b->dir_list[i], ft_strlen(b->dir_list[i + 1])))
		{
			temp = b->dir_list[i];
			b->dir_list[i] = b->dir_list[i + 1];
			b->dir_list[i + 1] = temp;
			i-=3;
		}
		i++;
		if (i < 0)
			i = 0;
	}
	//test_print_list(b, 'd');
}

void	sort_R_dirlist(t_ls *b)
{
	if (b->r && b->t)
		sort_rt(b);
	else if (b->r)
	{
	int		i;
	char	*temp;

	i = 0;
	while (b->dir_list[i] && b->dir_list[i + 1])
	{
		if (ft_strcmp(b->dir_list[i], b->dir_list[i + 1]) < 0 && \
		is_subdir_substr(b->dir_list[i], b->dir_list[i + 1], ft_strlen(b->dir_list[i])) == 0)
		{
			temp = b->dir_list[i];
			b->dir_list[i] = b->dir_list[i + 1];
			b->dir_list[i + 1] = temp;
			i-=3;
		}
		i++;
		if (i < 0)
			i = 0;
	}
	}
	else if (b->t)
	{
		int		i;
	char	*temp;
	struct stat f_status;
	long long	this_time;
	long long	next_time;
	sort_ascii(b->dir_list);

	i = 0;
	while (b->dir_list[i] && b->dir_list[i + 1])
	{
		stat(b->dir_list[i], &f_status);
		this_time = f_status.st_mtime;
		stat(b->dir_list[i + 1], &f_status);
		next_time = f_status.st_mtime;
		if (this_time < next_time && \
		is_subdir_substr(b->dir_list[i], b->dir_list[i + 1], ft_strlen(b->dir_list[i])) == 0)
		{
			temp =b->dir_list[i];
			b->dir_list[i] = b->dir_list[i + 1];
			b->dir_list[i + 1] = temp;
			i-=2;
		}
		i++;
		if (i < 0)
			i = 0;
	}
	}
	else
		sort_ascii(b->dir_list);
}
// sorts a given list with given conversion/flag
// t == time (-t), r == reverse (-r)

void	reverse_list(char **list)
{
	int i = 0;
	char *temp;
	int size;
	while (list[i])
	{
		i++;
	}
	//ft_printf("list contains %d many things\n", i);
	size = i;
	// ft_printf("first before reverse: %s\n", list[0]);
	// ft_printf("last before reverse: %s\n", list[size-1]);
	i = 0;
	while (i < size)
	{
		//ft_printf("swapping %d and %d\n", i, size-1);
		temp = list[size - 1];
		list[size - 1] = list[i];
		list[i] = temp;
		i++;
		size--;
	}
	// ft_printf("first after reverse: %s\n", list[0]);
	// ft_printf("last after reverse: %s\n", list[size-1]);
}

void	sort_list(char **list, char c, int r, char *path)
{
	//ft_printf("sortc is %c, r is on %d\n", c, r); //debug
	if (c == 't')
		sort_by_time(list, path);
	else
		if (c != 'f')
		sort_ascii(list);
	if (r == 1 && c != 'f')
		reverse_list(list);
}
