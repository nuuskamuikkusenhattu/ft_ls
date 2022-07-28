/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlink.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:34:41 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/28 16:37:46 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"
int main(void)
{
	DIR *d;
	struct dirent *dir;
	struct stat info;

	d = opendir(".");
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.') //needs better condition
			printf("%s\n", dir->d_name);
	}
	closedir(d);
	return (0);
}
