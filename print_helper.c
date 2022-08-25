/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:14:33 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/22 18:50:37 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	calc_column_and_row(t_ls *b)
{
	struct winsize	window;

	ioctl(0, TIOCGWINSZ, &window);
	b->columns = (window.ws_col) / (b->longest_name + 1);
	if (b->columns < 1)
		b->columns = 1;
	b->rows = b->file_count / b->columns;
	if (b->columns * b->rows != b->file_count)
		b->rows++;
	return (window.ws_col);
}

void	print_option_one(t_ls *b, int i)
{
	while (i < b->file_count)
	{
		ft_printf("%s", b->file_list[i]);
		if (i < b->file_count)
			write(1, "\n", 1);
		i++;
	}
}

void	print_column_format(t_ls *b, int total, int i, int j)
{
	while (total < b->file_count)
	{
		if (i + j <= b->file_count && b->file_list[i + j])
		{
			ft_printf("%-*s", b->longest_name + 1, b->file_list[i + j]);
			total++;
		}
		j += b->rows;
		if ((j >= (b->rows * b->columns)) || total == b->file_count)
		{
			j = 0;
			i++;
			write(1, "\n", 1);
		}
	}
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
