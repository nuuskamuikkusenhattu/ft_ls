/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:58:56 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/26 14:58:50 by spuustin         ###   ########.fr       */
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

void	sort(t_ls *b)
{
	if (b->t)
	{
		sort_time(b->dir_list); //emt pitaako paikkansa vai onko aina normi sort
		sort_time(b->file_list);
	}
	else if (b->r)
	{
		sort_ascii(b->dir_list);
		reverse_sort(b->file_list);
	}
	else
	{
		sort_ascii(b->non_exists);
		sort_ascii(b->file_list);
	}
}
