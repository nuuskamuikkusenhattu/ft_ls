/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:14:33 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/19 17:44:57 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	calc_column_and_row(t_ls *b)
{
	struct winsize	window;

	ioctl(0, TIOCGWINSZ, &window);
	b->columns = (window.ws_col)/ (b->longest_name + 1);
	if (b->columns < 1)
		b->columns = 1;
	b->rows = b->file_count / b->columns;
	if (b->columns * b->rows != b->file_count)
		b->rows++;
}

void	print_column_format(t_ls *b, int total, int i, int j)
{
	while (i < b->file_count)
	{
		ft_printf("%s\n", b->file_list[i]);
		i++;
	}
	// while (total < b->file_count)
	// {
	// 	if (i + j >= b->file_count - 1 && total < b->file_count)
	// 		j--;
	// 	if (b->file_list[i + j])
	// 	{
	// 		ft_printf("%-*s", b->longest_name + 1, b->file_list[i + j]);
	// 		total++;
	// 	}
	// 	j += b->rows;
	// 	if ((j >= (b->rows * b->columns)) || total == b->file_count)
	// 	{
	// 		j = 0;
	// 		i++;
	// 		write(1, "\n", 1);
	// 	}
	// }
}

void	print_with_serial_nro(t_ls *b)
{
	struct stat	info;
	int			i;
	char		*file_path;

	i = 0;
	while (b->file_list[i])
	{
		file_path = ft_strjoin(b->path, b->file_list[i]);
		lstat(file_path, &info);
		ft_printf("%d %s\n", info.st_ino, b->file_list[i]);
		i++;
	}
}
