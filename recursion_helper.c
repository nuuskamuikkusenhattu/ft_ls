/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:18:11 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/20 20:33:17 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	conditional_list_free(t_ls *b)
{
	if (b->file_count > 0)
		ft_free_array(b->file_list);
	else
	{
		free(b->file_list);
		b->file_list = NULL;
	}
}

void	recursion_helper(t_ls *b, char *current)
{
	conditional_list_free(b);
	count_all(b, current);
	init_list(b, 'f', b->file_count + 1);
	b->file_count = 0;
	list_files_in_dir(b, current);
	free(b->path);
	b->path = ft_strdup(current);
	if (b->file_count > 0 && b->l)
		get_total(b);
	print_files_only(b);
}
