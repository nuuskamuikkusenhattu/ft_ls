/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:54:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/12 19:01:35 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
//for directory operations (opendir)
#include <stdio.h>
//for system error message (perror)
#include <string.h>
//for system error message (strerror)
#include <sys/stat.h>
//for file status (stat, lstat)
#include <sys/types.h>
//for password database operations (getpwuid)
#include <grp.h>
#include <uuid/uuid.h>
//for fatabase operations
#include <sys/xattr.h>
//for listxattr/getxattr
#include "libft/libft.h"

#define FLAGS "lRrat"

typedef struct s_ls
{
	int	l;
	int r;
	int R;
	int a;
	int t;
	char **file_list;
	int	file_count;
	char **dir_list;
	int dir_count;
	char **non_exists;
	int	ne_count;
	int flagsParsed;
	int flag_args;
	char *path;
}	t_ls;

//parser
void	parser(int argc, char **argv, t_ls *build);

//list
void	create_lists(char **argv, t_ls *b);
void	list_all_in_current_dir(t_ls *b, char *path);

//sort
void	sort(t_ls *b);
void	sort_alphabetically(char **list);
void	reverse_sort(char **list);

//print
void	print_all(t_ls *build);

//testing
void	test_print_list(t_ls *b, char c);
void	test_show_params(t_ls *b);

#endif