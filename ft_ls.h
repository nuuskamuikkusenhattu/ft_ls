/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:54:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/18 14:07:43 by spuustin         ###   ########.fr       */
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

# define FLAGS "lRratfioT"
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
	int 	nameLen;
	int		columns;
	int		rows;
}	t_ls;

//build
void	initialize_list(t_ls *b, char c);

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

//sort
void	sort_list(char **list, char c, int r, char *path);
void	sort_ascii(char **list);
void	sort_by_time(char **list, char *path, int i, char *temp);
void	reverse_list(char **list);

//print
void	print(t_ls *b);
void	print_all_lists(t_ls *build);
void	print_files_only(t_ls *b);
void	print_non_existings(t_ls *b);

//long format
void	print_long_format(t_ls *b, int i, int ret);
int		print_permissions(struct stat f_status, char *path);
void	get_total(t_ls *b);
void	get_acl_data(char *path);

#endif
