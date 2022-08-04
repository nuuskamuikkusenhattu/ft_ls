/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:29:18 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/04 15:48:57 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// checks if str1 is a substring of str2 (subdirectory)

int		is_subdir_substr(char *str1, char *str2, int len1)
{
	if (strncmp(str1, str2, len1) == 0 && str2[len1] == '/')
		return (1);
	else
		return (0);
}

void	print_for_R(t_ls *b)
{
	int i = 0;
	
	b->ne_count = -1;
	while (b->dir_list[i])
	{
		if (b->dirfileargc != 1)
			ft_printf("%s:\n", b->dir_list[i]);
		b->dirfileargc = 42;
		initialize_list(b, 'f');
		b->path = ft_strdup(b->dir_list[i]);
		//protect
		list_files_in_dir(b, b->path);
		print_files_only(b);
		i++;
		if (i != b->dir_count)
			write(1, "\n", 1);
	}
}

void	R_start(t_ls *b)
{
	printf("sortc is %c\n\n", b->sortc);
	char **dirs;
	int i = 0;
	dirs = (char **)malloc(sizeof (char *) * b->dir_count + 1);
	//protect
	if (b->file_count > 0 && b->dir_count > 0)
		write(1, "\n", 1);
	if (b->r && b->t)
		sort_list(b->dir_list, 't');
	else
		sort_list(b->dir_list, b->sortc);
	while (b->dir_list[i])
	{
		dirs[i] = ft_strdup(b->dir_list[i]);
		//protect
		i++;
	}
	dirs[i] = NULL;
	i = 0;
	while (dirs[i])
	{
		initialize_list(b, 'd');
		b->dir_list[0] = ft_strdup(dirs[i]);
		b->dir_count = 1;
		//protect
		list_sub_directories(b);
		sort_R_dirlist(b);
		print_for_R(b);
		i++;
		if (dirs[i])
			write(1, "\n", 1);
	}
	exit(0);
}
