/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:36:39 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/16 18:31:57 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
if file/directory has extended security info (such as ACL),
a + is written after permissions

if file/directory has extended attributes, a '@' is written
*/

void get_acl_data(char *path)
{
	acl_t acl;
	int a;
	
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (acl)
		write(1, "+", 1);
	a = (int)listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (a > 0)
		write(1, "@", 1);
	free(acl);
}
