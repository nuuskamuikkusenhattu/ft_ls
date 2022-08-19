/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:40:09 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/19 20:49:04 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_file_mode(struct stat f_status)
{
	int		ret;

	ret = 0;
	if (S_ISDIR(f_status.st_mode))
		write(1, "d", 1);
	else if (S_ISLNK(f_status.st_mode))
	{
		write(1, "l", 1);
		ret = 1;
	}
	else if (S_ISCHR(f_status.st_mode))
	{
		write(1, "c", 1);
		ret = 2;
	}
	else if (S_ISBLK(f_status.st_mode))
	{
		write(1, "b", 1);
		ret = 2;
	}
	else
		write(1, "-", 1);
	return (ret);
}

static void	print_stickybit(struct stat f_status, int *rights)
{
	if (f_status.st_mode & rights[9] && f_status.st_mode & S_IXOTH)
		write(1, "t", 1);
	else if (f_status.st_mode & rights[9])
		write(1, "T", 1);
	else if (f_status.st_mode & rights[8])
		write(1, "x", 1);
	else
		write(1, "-", 1);
}

static void	help_print_permissions(struct stat f, int *rights, int i)
{
	while (i < 8)
	{
		if ((f.st_mode & rights[i]) && i % 3 == 0)
			write(1, "r", 1);
		else if ((f.st_mode & rights[i]) && i % 3 == 1)
			write(1, "w", 1);
		else if (i % 3 == 2)
		{
			if (((f.st_mode & S_ISUID && f.st_mode & S_IXUSR) && i == 2) || \
			((f.st_mode & S_ISGID && f.st_mode & S_IXGRP) && i == 5))
				write(1, "s", 1);
			else if ((f.st_mode & S_ISUID && i == 2) || \
			(f.st_mode & S_ISGID && i == 5))
				write(1, "S", 1);
			else if (f.st_mode & rights[i])
				write(1, "x", 1);
			else
				write(1, "-", 1);
		}
		else
			write(1, "-", 1);
		i++;
	}
}

int	print_permissions(struct stat f_status, char *path)
{
	static int	rights[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, \
	S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH, S_ISVTX, S_ISUID, S_ISGID};
	int			ret;

	ret = print_file_mode(f_status);
	help_print_permissions(f_status, rights, 0);
	print_stickybit(f_status, rights);
	get_acl_data(path);
	write(1, "  ", 2);
	return (ret);
}

void	get_total(t_ls *b)
{
	int			i;
	int			total;
	struct stat	data;
	char		*current;

	i = 0;
	total = 0;
	// while (i < b->file_count)
	// {
	// 	current = ft_strjoin(b->path, b->file_list[i]);
	// 	if (!current)
	// 		exit(1);
	// 	lstat(current, &data);
	// 	total += data.st_blocks;
	// 	if (current)
	// 	{
	// 		free(current);
	// 		current = NULL;
	// 	}
	// 	i++;
	// }
	// ft_printf("total %d\n", total);
}
