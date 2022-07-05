/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:34:08 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/05 15:08:25 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
checks that a arguments-string contains only one dash (-),
and only wanted chars
returns 1 if all good, 0 if invalid argument
*/
static int	validate_flags(char *str)
{
	int i;

	i = 0;
	if (str[i++] != '-')
	{
		ft_printf("ls: %s: No such file or directory\n", str);
		return (0);
	}
	else
	{
		while (str[i])
		{
			if (ft_strchr(FLAGS, str[i]) == NULL)
				return (-1);
			i++;
		}
	}
	return (1);
}

// parses and validates the arguments
void	parser(int argc, char **argv, t_ls *build)
{
	int 	a;
	int		ret;

	a = 1;
	printf("in parser\n");
	while (a < argc)
	{
		ret = validate_flags(argv[a]);
		if (ret == -1)
		{
			ft_printf("ls: illegal option -- %c\n", argv[a][0]);
			ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
		}
		else if (ret == 1)
			printf("all good everything");
		a++;
	}
}