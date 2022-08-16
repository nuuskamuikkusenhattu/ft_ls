/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:58:56 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/16 21:11:55 by spuustin         ###   ########.fr       */
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
			i -= 2;
		}
		i++;
		if (i < 0)
			i = 0;
	}
}

// MAY be useful

// void	reverse_ascii(char **list)
// {
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	while (list[i] && list[i + 1])
// 	{
// 		if (ft_strcmp(list[i], list[i + 1]) < 0)
// 		{
// 			temp = list[i];
// 			list[i] = list[i + 1];
// 			list[i + 1] = temp;
// 			i-=2;
// 		}
// 		i++;
// 		if (i < 0)
// 			i = 0;
// 	}
// }

void	sort_by_time(char **list, char *path)
{
	int			i;
	char		*temp;
	struct stat	f_status;
	long long	this_time[2];
	long long	next_time[2];
	char		*current;

	sort_ascii(list);
	i = 0;
	while (list[i] && list[i + 1])
	{
		current = ft_strjoin(path, list[i]);
		lstat(current, &f_status);
		this_time[0] = f_status.st_mtime;
		this_time[1] = f_status.st_mtimespec.tv_nsec;
		free(current);
		current = ft_strjoin(path, list[i + 1]);
		lstat(current, &f_status);
		free(current);
		next_time[0] = f_status.st_mtime;
		next_time[1] = f_status.st_mtimespec.tv_nsec;
		if (this_time[0] < next_time[0] || (this_time[0] == next_time[0] \
		&& this_time[1] < next_time[1]))
		{
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			i -= 3;
		}
		i++;
		if (i < 0)
			i = 0;
	}
}

void	reverse_list(char **list)
{
	int		i;
	char	*temp;
	int		size;

	i = 0;
	while (list[i])
	{
		i++;
	}
	size = i;
	i = 0;
	while (i < size)
	{
		temp = list[size - 1];
		list[size - 1] = list[i];
		list[i] = temp;
		i++;
		size--;
	}
}

void	sort_list(char **list, char c, int r, char *path)
{
	if (c == 't')
		sort_by_time(list, path);
	else
		if (c != 'f')
			sort_ascii(list);
	if (r == 1 && c != 'f')
		reverse_list(list);
}
