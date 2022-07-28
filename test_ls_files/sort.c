/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:58:56 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/26 17:16:43 by spuustin         ###   ########.fr       */
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

void	reverse_sort(char **list)
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

	i = 0;
	while (list[i] && list[i + 1])
	{
		stat(list[i], &f_status);
		this_time = f_status.st_mtime;
		stat(list[i + 1], &f_status);
		next_time = f_status.st_mtime;
		if (this_time < next_time)
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

// sorts a given list with given conversion/flag
// t == time (-t), r == reverse (-r)

void	sort_list(char **list, char c)
{
	if (c == 't')
		sort_time(list);
	else if (c == 'r')
		reverse_sort(list);
	else
		sort_ascii(list);
}
