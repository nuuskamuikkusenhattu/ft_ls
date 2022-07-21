/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:40:33 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/21 12:23:23 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
The stat() function gets status information about a specified file and places 
it in the area of memory pointed to by the buf argument. If the named file is 
a symbolic link, stat() resolves the symbolic link. It also returns information
about the resulting file.
*/

void	print_long_format(t_ls *b)
{
	struct stat	f_status;
	int		i = 0;
	int exists = 0;
	printf("reached the function, fc is %d\n", b->file_count);
	while (b->file_list[i]) //voi olla et normi-ongelma
	{
		if (stat(b->file_list[i], &f_status) < 0)
			printf("doesnt exist");
		ft_printf("file size of %s is: %d\n", b->file_list[i], f_status.st_size);
		i++;
	}
}
