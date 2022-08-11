/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:34:08 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/11 22:22:27 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_flag(t_ls *build, char c)
{
	if (c == 'l')
		build->l = 1;
	if (c == 'a')
		build->a = 1;
	if (c == 't')
		build->t = 1;
	if (c == 'r')
		build->r = 1;
	if (c == 'R')
		build->R = 1;
	if (c == 'd')
		build->d = 1;
	if (c == 'f')
		build->f = 1;
	if (c == 'i')
		build->option_i = 1;
}

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
static int	validate_flags(char *str, t_ls *build)
{
	int i;

	i = 0;
	if ((str[i] != '-' || !str[i + 1]) && build->flagsParsed == 0)
	{
		build->flagsParsed = 1;
		return (0);
	}
	else if (str[i] == '-' && str[i + 1] == '-' && !str[i + 2])
	{
		build->flagsParsed = 1;
		build->flag_args++;
		return (1);
	}
	else
	{
		while (str[++i])
		{
			if (ft_strchr(FLAGS, str[i]) == NULL)
				return (-1);
			set_flag(build, str[i]);
		}
	}
	build->flag_args++;
	return (1);
}


/*

*/
void	parser(int argc, char **argv, t_ls *build)
{
	int 	a;
	int		ret;

	a = 1;
	ret = 1;
	while (a < argc && ret == 1 && build->flagsParsed == 0)
	{
		ret = validate_flags(argv[a], build);
		if (ret == -1)
		{
			ft_printf("ft_ls: illegal option -- %c\n", argv[a][err_option(argv[a])]);
			ft_printf("usage: ft_ls [-altrRd] [file ...]\n");
			exit(1); //may need to free here
		}
		a++;
	}
	if (build->t)
		build->sortc = 't';
	if (build->f)
	{
		build->a = 1;
		build->sortc = 'f';
	}
	build->dirfileargc = argc - 1 - build->flag_args;
}
