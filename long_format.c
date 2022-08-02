/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:40:33 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/02 13:00:27 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
The stat() function gets status information about a specified file and places 
it in the area of memory pointed to by the buf argument. If the named file is 
a symbolic link, stat() resolves the symbolic link. It also returns information
about the resulting file.
*/

static int	print_permissions(struct stat f_status)
{
	int	rights[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	int i = 0;
	int	ret = 0;

	if (S_ISDIR(f_status.st_mode))
		ft_printf("d");
	else if (S_ISLNK(f_status.st_mode))
	{
		ft_printf("l");
		ret = 1;
	}
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
	return (ret);
}
// prints path of link

static void	print_link(char *name)
{
	char buf[MAX_PATH];
	ssize_t len;

	len = readlink(name, buf, MAX_PATH);
	if (len != -1)
		ft_printf(" -> %s", buf);
}

/*
splits time-str into array
[0] = day (never needed), [1] = month, [2] = day, [3] = hh:mm:ss, [4] = year
depending on how old the file is, either year or hhmmss is printed

15778476
*/
static void	parse_time(struct stat f_status, char *str)
{
	char	**this_time;
	char	*parsed;
	time_t	now;

	this_time = ft_strsplit(str, ' ');
	parsed = ft_strnew(5);
	ft_strncpy(parsed, this_time[3], 5);
	if (time(&now) - f_status.st_mtime < 15724800)
		ft_printf("%s %s %s ", this_time[1], this_time[2], parsed);
	else
		ft_printf("%s %s %s ", this_time[1], this_time[2], ft_strtrim(this_time[4]));
}

void	print_long_format(t_ls *b)
{
	struct stat	f_status;
	struct passwd *pw;
	struct group *gp;
	int		i = 0;
	int exists = 0;
	int islink = 0;
	char *file_path;
	while (b->file_list[i])
	{
		file_path = ft_strjoin(b->path, b->file_list[i]);
		if (lstat(file_path, &f_status) > -1)
		{
			islink = print_permissions(f_status);
			pw = getpwuid(f_status.st_uid);
			gp = getgrgid(f_status.st_gid);
			ft_printf("%d %s  %s %d ", f_status.st_nlink, pw->pw_name, \
			gp->gr_name, f_status.st_size);
			parse_time(f_status, ctime(&f_status.st_mtime));
			ft_printf("%s", b->file_list[i]);
			if (islink == 1)
				print_link(b->file_list[i]);
			write(1, "\n", 1);
		}
		i++;
	}
}
