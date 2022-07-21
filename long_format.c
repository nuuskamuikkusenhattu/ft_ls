/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:40:33 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/21 16:16:42 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
The stat() function gets status information about a specified file and places 
it in the area of memory pointed to by the buf argument. If the named file is 
a symbolic link, stat() resolves the symbolic link. It also returns information
about the resulting file.
*/

static void	print_permissions(struct stat f_status)
{
	int	rights[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	int i = 0;

	if (S_ISDIR(f_status.st_mode))
		ft_printf("d");
	else
		ft_printf("-");
	while (i < 9)
	{
		if ((f_status.st_mode & rights[i]) && i % 3 == 0)
			ft_printf("r");
		else if ((f_status.st_mode & rights[i]) && i % 3 == 1)
			ft_printf("w");
		else if ((f_status.st_mode & rights[i]) && i % 3 == 2)
			ft_printf("x");
		else
			ft_printf("-");
		i++;
	}
	ft_printf("  ");
}

void	print_long_format(t_ls *b)
{
	struct stat	f_status;
	struct passwd *pw;
	struct group *gp;
	int		i = 0;
	int exists = 0;
	//printf("reached the function, fc is %d\n", b->file_count); //debug
	while (b->file_list[i])
	{
		if (stat(b->file_list[i], &f_status) > -1)
		{
		print_permissions(f_status);
		pw = getpwuid(f_status.st_uid);
		gp = getgrgid(f_status.st_gid);
		ft_printf("%d %s  %s %d %d ", f_status.st_nlink, pw->pw_name, \
		gp->gr_name, f_status.st_nlink, f_status.st_size);
		ft_printf("%s", b->file_list[i]);
		//trying to get the date to print right
		ft_printf("%s", ctime(&f_status.st_mtime));
		}
		i++;
	}
}
