/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:54:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/25 15:00:01 by spuustin         ###   ########.fr       */
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
#include <pwd.h>
//for password database operations (getpwuid)
#include <grp.h>
#include <uuid/uuid.h>
//for database operations
#include <sys/xattr.h>
//for listxattr/getxattr
#include "libft/libft.h"
//for ctime
#include <time.h>

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
	int	R_done;
	int argc;
}	t_ls;

//build
void	initialize_list(t_ls *b, char c);

//parser
void	parser(int argc, char **argv, t_ls *build);

//list
void	create_lists(char **argv, int argc, t_ls *b);
void	list_files_in_dir(t_ls *b, char *path);
void	list_files_only(t_ls *b);
void	list_directories_only(t_ls *b);
void	list_sub_directories(t_ls *b);

//sort
void	sort(t_ls *b);
void	sort_ascii(char **list);
void	sort_time(char **list);
void	reverse_sort(char **list);

//print
void	print(t_ls *b);
void	print_all(t_ls *build);
void	print_files_only(t_ls *b);
void	print_dir_content(t_ls *b);
void	print_non_existings(t_ls *b);
void	print_R(t_ls *b);

//testing
void	test_print_list(t_ls *b, char c);
void	test_show_params(t_ls *b);

//long format
void	print_long_format(t_ls *b);

#endif