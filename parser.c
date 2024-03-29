/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:34:08 by spuustin          #+#    #+#             */
/*   Updated: 2022/08/20 16:03:23 by spuustin         ###   ########.fr       */
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
	{
		build->t = 1;
		build->sortc = 't';
	}
	if (c == 'r')
		build->r = 1;
	if (c == 'R')
		build->capital_r = 1;
	if (c == 'f')
		build->f = 1;
	if (c == 'i')
		build->option_i = 1;
	if (c == 'o')
		build->o = 1;
	if (c == 'T')
		build->capitalt = 1;
	if (c == '1')
		build->option_one = 1;
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
	int		i;

	i = 0;
	if ((str[i] != '-' || !str[i + 1]) && build->flags_parsed == 0)
	{
		build->flags_parsed = 1;
		return (0);
	}
	else if (str[i] == '-' && str[i + 1] == '-' && !str[i + 2])
	{
		build->flags_parsed = 1;
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

void	parser(int argc, char **argv, t_ls *build)
{
	int		a;
	int		ret;

	a = 1;
	ret = 1;
	while (a < argc && ret == 1 && build->flags_parsed == 0)
	{
		ret = validate_flags(argv[a], build);
		if (ret == -1)
		{
			ft_printf("ft_ls: illegal option -- %c\n", \
			argv[a][err_option(argv[a])]);
			ft_printf("usage: ft_ls [-altrRfioT1] [file ...]\n");
			exit(1);
		}
		a++;
	}
	if (build->f)
	{
		build->a = 1;
		build->sortc = 'f';
	}
	if (build->o)
		build->l = 1;
	build->dirfileargc = argc - 1 - build->flag_args;
}
