/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlink.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:34:41 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/29 12:55:57 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"
int main(void)
{
	DIR *d;
	struct dirent *dir;
	struct stat info;
	ssize_t len;
	char buf[500];

	d = opendir(".");
	while ((dir = readdir(d)) != NULL)
	{
		lstat(dir->d_name, &info);
		if (S_ISLNK(info.st_mode))
		{
			len = readlink(dir->d_name, buf, 500);
			printf("%s returned %zd\n", dir->d_name, len);
			printf("buf includes: %s\n", buf);
		}
	}
	closedir(d);
	return (0);
}
