/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:40:33 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/26 15:15:17 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
The lstat() function gets status information about a specified file and places 
it in the area of memory pointed to by the buf argument. It also
returns information about the resulting file.
*/

// prints path of symbolic link

static void	print_link(char *name)
{
	char	buf[MAX_PATH + 1];
	ssize_t	len;

	ft_bzero(buf, MAX_PATH + 1);
	len = readlink(name, buf, MAX_PATH + 1);
	if (len != -1)
		ft_printf(" -> %s", buf);
}

/*
splits time-str into array
[0] = day (never needed), [1] = month, [2] = day, [3] = hh:mm:ss, [4] = year
depending on how old the file is, either year or hhmmss is printed
*/
static void	parse_time(struct stat data, char *str)
{
	char	**this_time;
	char	*parsed;
	char	*trim;
	time_t	now;

	this_time = ft_strsplit(str, ' ');
	if (!this_time)
		exit(1);
	parsed = ft_strnew(5);
	if (!parsed)
		exit(1);
	ft_strncpy(parsed, this_time[3], 5);
	if (time(&now) - data.st_mtime < 15778476 && \
	time(&now) - data.st_mtime > 0)
		ft_printf("%s %s %s ", this_time[1], this_time[2], parsed);
	else
	{
		trim = ft_strtrim(this_time[4]);
		ft_printf("%s %s %s ", this_time[1], this_time[2], trim);
		free(trim);
	}
	ft_free_array(this_time);
	free(parsed);
}

static void	pw_and_gp(struct stat d, struct passwd *p, struct group *g, t_ls *b)
{
	if (p)
		ft_printf("%-4d %-10s   ", d.st_nlink, p->pw_name);
	else
		ft_printf("%-4d %-10lld   ", d.st_nlink, d.st_uid);
	if (!b->o)
	{
		if (g)
			ft_printf("%-6s  ", g->gr_name);
		else
			ft_printf("%-6lld  ", d.st_gid);
	}
}

static void	print_long_data(t_ls *b, struct stat data, char *time, int ret)
{
	struct passwd	*pw;
	struct group	*gp;

	pw = getpwuid(data.st_uid);
	gp = getgrgid(data.st_gid);
	pw_and_gp(data, pw, gp, b);
	if (ret == 2)
	{
		if (minor(data.st_rdev) > 500)
			ft_printf("%u,  %010p ", major(data.st_rdev), minor(data.st_rdev));
		else
			ft_printf("%u,  %u ", major(data.st_rdev), minor(data.st_rdev));
	}
	else
		ft_printf("%5d ", data.st_size);
	if (!b->capitalt)
		parse_time(data, ctime(&data.st_mtime));
	else
	{
		time = ft_strtrim(ctime(&data.st_mtime));
		if (!time)
			exit(1);
		ft_printf("%s ", time + 4);
		free(time);
	}
}

void	print_long_format(t_ls *b, int i, int ret)
{
	struct stat		data;
	acl_t			acl;
	char			*file_path;

	while (i < b->file_count)
	{
		file_path = ft_strjoin(b->path, b->file_list[i]);
		if (!file_path)
			exit(1);
		acl = acl_get_file(file_path, ACL_TYPE_EXTENDED);
		if (lstat(file_path, &data) > -1)
		{
			if (b->option_i)
				ft_printf("%d ", data.st_ino);
			ret = print_permissions(data, file_path);
			print_long_data(b, data, NULL, ret);
			ft_printf("%s", b->file_list[i]);
			if (ret == 1)
				print_link(file_path);
			write(1, "\n", 1);
		}
		free(file_path);
		free(acl);
		i++;
	}
}
