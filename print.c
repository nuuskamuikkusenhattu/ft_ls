/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:05:26 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/22 18:33:42 by spuustin         ###   ########.fr       */
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

	i = 0;
	sort_ascii(b->non_exists);
	while (b->non_exists[i])
	{
		if (ft_strlen(b->non_exists[i]) > 255)
			ft_printf("ft_ls: %s: File name too long\n", b->non_exists[i]);
		else
			ft_printf("ft_ls: %s: No such file or directory\n", \
			b->non_exists[i]);
		i++;
	}
	b->errno = 1;
}

void	print_files_only(t_ls *b)
{
	if (b->file_count > 1)
		sort_list(b->file_list, b->sortc, b->r, b->path);
	if (b->l)
		print_long_format(b, 0, 0);
	else if (b->option_i)
		print_with_serial_nro(b);
	else if (b->option_one == 1)
		print_option_one(b, 0);
	else
	{
		calc_column_and_row(b);
		print_column_format(b, 0, 0, 0);
	}
	b->longest_name = 0;
}

void	print_all_helper(t_ls *b, int i, char *current)
{
	if (b->dir_list[i][ft_strlen(b->dir_list[i]) - 1] == '/')
		b->path = ft_strdup(b->dir_list[i]);
	else
	{
		current = ft_strjoin(b->dir_list[i], "/");
		b->path = ft_strdup(current);
		ft_memdel((void *)&current);
	}
	if (b->dirfileargc > 1)
		ft_printf("%s:\n", b->dir_list[i]);
	if (b->file_count > 0)
		ft_free_array(b->file_list);
	else
	{
		free(b->file_list);
		b->file_list = NULL;
	}
	count_all(b, b->path);
	init_list(b, 'f', b->file_count + 1);
	b->file_count = 0;
	list_files_in_dir(b, b->dir_list[i]);
	if (b->l && (b->dirfileargc == 0 || b->file_count != 0))
		get_total(b);
	print_files_only(b);
}

void	print_all_lists(t_ls *b, int i)
{
	if (b->non_exists > 0)
		print_non_existings(b);
	if (b->dirfileargc == 0 && b->l)
	{
		get_total(b);
	}
	if (b->file_count > 0)
		print_files_only(b);
	if (b->file_count > 0 && b->dir_count != 0)
		write(1, "\n", 1);
	if (b->dir_count > 0)
	{
		sort_list(b->dir_list, b->sortc, b->r, b->path);
		while (b->dir_list[i])
		{
			print_all_helper(b, i, NULL);
			i++;
			ft_memdel((void *)&b->path);
			if (b->dir_list[i])
				write(1, "\n", 1);
		}
	}
}

void	print(t_ls *b, int i)
{
	if (b->capital_r)
	{
		if (b->ne_count > 0)
			print_non_existings(b);
		b->ne_count = -1;
		print_files_only(b);
		if (b->dir_count > 0 && b->file_count > 0)
			write(1, "\n", 1);
		sort_list(b->dir_list, b->sortc, b->r, b->path);
		while (b->dir_list[i])
		{
			print_all_dirs(b, i);
			i++;
			if (b->path)
			{
				free(b->path);
				b->path = NULL;
			}
			if (b->dir_list[i])
				write(1, "\n", 1);
		}
	}
	else
		print_all_lists(b, 0);
}
