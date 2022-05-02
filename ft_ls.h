/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:54:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/05/02 14:08:38 by spuustin         ###   ########.fr       */
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
}	t_flags;

#endif