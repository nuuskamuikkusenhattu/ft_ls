/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:54:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/05/05 15:29:26 by spuustin         ###   ########.fr       */
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

#define FLAGS = "lRrat"

typedef struct s_flags
{
	int	l;
	int r;
	int R;
	int a;
	int t;
	int	file_count;
	char **list;
}	t_flags;

//list
void	print_list(t_flags *b);
void	print_files(t_flags *b);
void	create_list(t_flags *b);
void	sort_alphabetically(t_flags *b);


#endif