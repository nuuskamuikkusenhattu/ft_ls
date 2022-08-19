/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:58:56 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/19 18:25:15 by spuustin         ###   ########.fr       */
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

/*
int array times contains 4 values.
first 2 are modific. time and nanosec for first file,
and the next two are for the one.
*/

static void	string_swap(char **first, char **second, char **temp)
{
	*temp = *first;
	*first = *second;
	*second = *temp;
}

void	sort_by_time(char **list, char *path, int i, char *current)
{
	struct stat	f_status;
	long long	times[4];

	while (list[i] && list[i + 1])
	{
		current = ft_strjoin(path, list[i]);
		lstat(current, &f_status);
		times[0] = f_status.st_mtime;
		times[1] = f_status.st_mtimespec.tv_nsec;
		free(current);
		current = NULL;
		current = ft_strjoin(path, list[i + 1]);
		lstat(current, &f_status);
		free(current);
		current = NULL;
		times[2] = f_status.st_mtime;
		times[3] = f_status.st_mtimespec.tv_nsec;
		if (times[0] < times[2] || (times[0] == times[2] \
		&& times[1] < times[3]))
		{
			string_swap(&list[i], &list[i + 1], &current);
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
	{
		sort_ascii(list);
		sort_by_time(list, path, 0, NULL);
	}
	else
		if (c != 'f')
			sort_ascii(list);
	if (r == 1 && c != 'f')
		reverse_list(list);
}
