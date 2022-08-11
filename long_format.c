/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:40:33 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/11 22:36:01 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
The lstat() function gets status information about a specified file and places 
it in the area of memory pointed to by the buf argument. It also
returns information about the resulting file.
*/

static int	print_permissions(struct stat f_status)
{
	int	rights[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH, S_ISVTX, S_ISUID, S_ISGID};
	int i = 0;
	int	ret = 0;

	if (S_ISDIR(f_status.st_mode))
		ft_printf("d");
	else if (S_ISLNK(f_status.st_mode))
	{
		ft_printf("l");
		ret = 1;
	}
	else if (S_ISCHR(f_status.st_mode))
	{
		ft_printf("c");
		ret = 2;
	}
	else if (S_ISBLK(f_status.st_mode))
	{
		ft_printf("b");
		ret = 2;
	}
	else
		ft_printf("-");
	while (i < 8)
	{
		if ((f_status.st_mode & rights[i]) && i % 3 == 0)
			ft_printf("r");
		else if ((f_status.st_mode & rights[i]) && i % 3 == 1)
			ft_printf("w");
		else if (i % 3 == 2)
		{
			if (((f_status.st_mode & S_ISUID && f_status.st_mode & S_IXUSR) && i == 2) ||( (f_status.st_mode & S_ISGID && f_status.st_mode & S_IXGRP) && i == 5))
				ft_printf("s");
			else if ((f_status.st_mode & S_ISUID && i == 2) || (f_status.st_mode & S_ISGID && i == 5))
				ft_printf("S"); //need to handle s, too
			else if (f_status.st_mode & rights[i])
				ft_printf("x");
			else
				ft_printf("-");
		}
		else
			ft_printf("-");
		i++;
	}
	if (f_status.st_mode & rights[9] && f_status.st_mode & S_IXOTH)
		ft_printf("t"); //need to handle T, too (i think)
	else if (f_status.st_mode & rights[9])
		ft_printf("T");
	else if (f_status.st_mode & rights[8])
		ft_printf("x");
	else
		ft_printf("-");
	ft_printf("  ");
	return (ret);
}
// prints path of link

static void	print_link(char *name)
{
	char buf[MAX_PATH + 1];
	ssize_t len;

	ft_bzero(buf, MAX_PATH + 1);
	len = readlink(name, buf, MAX_PATH + 1);
	if (len != -1)
		ft_printf(" -> %s", buf);
	else
		printf("%s", strerror(len));
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
	parsed = ft_strnew(5); //protect
	ft_strncpy(parsed, this_time[3], 5);
	if (time(&now) - f_status.st_mtime < 15724800 && time(&now) - f_status.st_mtime > 0)
		ft_printf("%s %s %s ", this_time[1], this_time[2], parsed);
	else
		ft_printf("%s %s %s ", this_time[1], this_time[2], ft_strtrim(this_time[4]));
}

void	get_total(t_ls *b)
{
	int i;
	int total;
	struct stat f_status;
	char *current;

	i = 0;
	total = 0;
	while (b->file_list[i])
	{
		current = ft_strjoin(b->path, b->file_list[i]);
		//printf("path is %s\n", b->path);
		lstat(current, &f_status);
		total += f_status.st_blocks;
		//printf("%s : %lld\n", b->file_list[i], f_status.st_blocks);
		i++;
	}
	ft_printf("total %d\n", total);
}

void	print_long_format(t_ls *b)
{
	struct stat	f_status;
	struct passwd *pw;
	struct group *gp;
	int		i = 0;
	int exists = 0;
	int ret = 0;
	char *file_path;
	
	//get_total(b); //some unknown condition
	while (b->file_list[i])
	{
		file_path = ft_strjoin(b->path, b->file_list[i]);
		if (lstat(file_path, &f_status) > -1)
		{
			if (b->option_i)
				ft_printf("%d ", f_status.st_ino);
			ret = print_permissions(f_status);
			pw = getpwuid(f_status.st_uid);
			gp = getgrgid(f_status.st_gid);
			ft_printf("%d %s  %s ", f_status.st_nlink, pw->pw_name, \
			gp->gr_name);
			if (ret == 2)
				ft_printf("%u,   %u ", major(f_status.st_rdev), minor(f_status.st_rdev)); //should print the weird size data for b and c
			else
				ft_printf("%d ", f_status.st_size);
			parse_time(f_status, ctime(&f_status.st_mtime));
			ft_printf("%s", b->file_list[i]);
			if (ret == 1)
				print_link(file_path);
			write(1, "\n", 1);
		}
		i++;
	}
}
