/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:34:08 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/05 15:32:35 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	err_option(char *str)
{
	int		i;
	
	i = 1;
	while (str[i])
	{
		if (ft_strchr(FLAGS, str[i]) == NULL)
			return (i);
		i++;
	}
	return (-1);
}

/*
checks that a arguments-string contains only one dash (-),
and only wanted chars
returns 1 if all good, 0 if invalid argument
*/
static int	validate_flags(char *str)
{
	int i;

	i = 0;
	if (!str || str[i] != '-' || !str[i + 1])
	{
		ft_printf("ls: %s: No such file or directory\n", str);
		return (0);
	}
	else
	{
		while (str[++i])
		{
			if (ft_strchr(FLAGS, str[i]) == NULL)
				return (-1);
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
	ret = 1;
	while (a < argc && ret == 1)
	{
		ret = validate_flags(argv[a]);
		if (ret == -1)
		{
			ft_printf("ls: illegal option -- %c\n", argv[a][err_option(argv[a])]);
			ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] \
			[file ...]\n");
		}
		a++;
	}
}