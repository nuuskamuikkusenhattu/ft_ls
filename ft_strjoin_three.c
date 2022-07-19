/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:01:13 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/19 20:51:47 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>

static void	strjoin_helper(char *dest, char *src, int i)
{
	int		j;

	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i + 1] = '\0';
}

char	*ft_strjoin_three(char *dest, char *src1, char *src2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!dest || !src1 || !src2)
		return (NULL);
	ret = (char *)malloc(sizeof(ft_strlen(dest) + ft_strlen(src1) \
	+ ft_strlen(src2)) + 1);
	if (!ret)
		return (NULL);
	while (dest[i])
	{
		ret[i] = dest[i];
		i++;
	}
	while (src1[j])
	{
		ret[i] = src1[j];
		i++;
		j++;
	}
	strjoin_helper(ret, src2, i);
	return (ret);
}
