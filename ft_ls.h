/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:54:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/16 20:41:34 by spuustin         ###   ########.fr       */
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
//for database operations (getpwuid)
#include <grp.h>
#include <uuid/uuid.h>
//for database operations
#include <sys/xattr.h>
//for listxattr/getxattr
#include <time.h>
//for ctime
#include <sys/acl.h>
// for acl bonus
#include <sys/ioctl.h>
// for column-bonus
#include "libft/libft.h"

#define FLAGS "lRratfioT"
#define MAX_PATH 256

typedef struct s_ls
{
	int	l;
	int r;
	int R;
	int a;
	int t;
	int f;
	int	option_i;
	int o;
	int option_T;
	char sortc;
	char **file_list;
	int	file_count;
	char **dir_list;
	int dir_count;
	char **non_exists;
	int	ne_count;
	int flagsParsed;
	int flag_args;
	char *path;
	int	i;
	int argc;
	int	dirfileargc;
	int longest_name;
}	t_ls;

//build
void	initialize_list(t_ls *b, char c);

//parser
void	parser(int argc, char **argv, t_ls *build);

//list
void	create_lists(char **argv, int argc, t_ls *b);
void	list_files_in_dir(t_ls *b, char *path);
void	list_files_only(t_ls *b);
//void	list_directories_only(t_ls *b);
//void	list_sub_directories(t_ls *b);

//sort
void	sort_list(char **list, char c, int r, char *path);
void	sort_ascii(char **list);
//void	sort_time(char **list);
void	sort_by_time(char **list, char *path);
//void	reverse_ascii(char **list);
void	reverse_list(char **list);
//void	sort_rt(t_ls *b);

//print
void	print(t_ls *b);
void	print_all_lists(t_ls *build);
void	print_files_only(t_ls *b);
//void	print_dir_content(t_ls *b);
void	print_non_existings(t_ls *b);
//void	print_R(t_ls *b);

//testing
void	test_print_list(t_ls *b, char c);
void	test_show_params(t_ls *b);

//long format
void	print_long_format(t_ls *b);
void 	test_print_this_list(char **list);
void	get_total(t_ls *b);
void	get_acl_data(char *path);

//being playful
//void	R_start(t_ls *b);
//int		is_subdir_substr(char *str1, char *str2, int len1);
//void	sort_R_dirlist(t_ls *b);
#endif

