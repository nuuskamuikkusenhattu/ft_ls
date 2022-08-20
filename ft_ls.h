/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:54:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/20 16:02:33 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
//for directory operations (opendir)
# include <stdio.h>
//for system error message (perror)
# include <string.h>
//for system error message (strerror)
# include <sys/stat.h>
//for file status (stat, lstat)
# include <sys/types.h>
# include <pwd.h>
//for database operations (getpwuid)
# include <grp.h>
# include <uuid/uuid.h>
//for database operations
# include <sys/xattr.h>
//for listxattr/getxattr
# include <time.h>
//for ctime
# include <sys/acl.h>
// for acl bonus
# include <sys/ioctl.h>
// for column-bonus
# include "libft/libft.h"

# define FLAGS "lRratfioT1"
# define MAX_PATH 256

typedef struct s_ls
{
	int		l;
	int		r;
	int		capital_r;
	int		a;
	int		t;
	int		f;
	int		option_i;
	int		o;
	int		capitalt;
	int		option_one;
	char	sortc;
	char	**file_list;
	int		file_count;
	char	**dir_list;
	int		dir_count;
	char	**non_exists;
	int		ne_count;
	int		flags_parsed;
	int		flag_args;
	char	*path;
	int		i;
	int		argc;
	int		dirfileargc;
	int		longest_name;
	int		exists;
	int 	name_len;
	int		columns;
	int		rows;
}	t_ls;

//build
void	initialize_list(t_ls *b, char c);
void	init_list(t_ls *build, char c, int count);
void	count_all(t_ls *b, char *path);

//parser
void	parser(int argc, char **argv, t_ls *build);

//list
void	create_lists(char **argv, int argc, t_ls *b);
void	list_files_in_dir(t_ls *b, char *path);
void	list_files_only(t_ls *b);
void	list_link_helper(t_ls *b, char **argv, char *buf, int i);
void	add_to_dirlist(t_ls *b, char *name);
void	check_longest(t_ls *b, int len);
void	list_link(t_ls *b, char **argv, int i, int x);
void	list_file(t_ls *b, struct stat path, char **argv, int i);

//sort
void	sort_list(char **list, char c, int r, char *path);
void	sort_ascii(char **list);
void	sort_by_time(char **list, char *path, int i, char *temp);
void	reverse_list(char **list);

//print
void	print(t_ls *b, int i);
void	print_all_lists(t_ls *build, int i);
void	print_files_only(t_ls *b);
void	print_non_existings(t_ls *b);
void	print_column_format(t_ls *b, int total, int i, int j);
void	calc_column_and_row(t_ls *b);
void	print_with_serial_nro(t_ls *b);
void	print_option_one(t_ls *b, int i);

//long format
void	print_long_format(t_ls *b, int i, int ret);
int		print_permissions(struct stat f_status, char *path);
void	get_total(t_ls *b);
void	get_acl_data(char *path);

//recursion
void	print_all_dirs(t_ls *b, int i);
void	recursion(t_ls *b, char *path);
int		count_dirs(char *path);

#endif
