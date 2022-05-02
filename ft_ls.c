/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:26:53 by spuustin          #+#    #+#             */
/*   Updated: 2022/05/02 16:10:50 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Within your mandatory part you are allowed to use the following functions:
◦ write
opendir, readdir, closedir 
◦ stat; lstat
◦ getpwuid ◦ getgrgid ◦ listxattr ◦ getxattr 
◦ time, ctime
◦ readlink 
◦ malloc, free
◦ perror, strerror ◦ exit

For each operand that names a file of a type other than directory, ls displays its name as well as any
     requested, associated information.  For each operand that names a file of type directory, ls displays the
     names of files contained within that directory, as well as any requested, associated information.

     If no operands are given, the contents of the current directory are displayed.  If more than one operand is
     given, non-directory operands are displayed first; directory and non-directory operands are sorted sepa-
     rately and in lexicographical order.

Amongst the numerous options available, we are asking you to create the
following: -l, -R, -a, -r and -t.
We strongly recommend that you account for the implications of the
option -R from the very beginning of your code...

You do not have to deal with the multiple column format for the exit when
the option -l isn’t in the arguments.
◦ You are not required to deal with ACL and extended attributes.
◦ The overall display, depending on each option, must stay as identical as pos- sible to the system command. 
We will be cordial when grading either the padding or the pagination, but no information can be missing.

-l = list in long-format. if the output is to a terminal, a total sum for all
the file sizes is output on a line before the long listing.
-R = recursively list subdirectories encountered. !!!
-a = include directory entries whose names begin with a dot '.'
-r = reverse the order of the sort to reverse lexicographical order or the 
oldest entries first (or largest files last, if combined with sort by size)
-t = sort by time modifie (most recently modified first) before sorting
the operands by lexicographical order.
*/

#include "ft_ls.h"

int	is_valid_char(char c)
{
	char *valids;

	valids = "laRrt";
	while (*valids)
	{
		if (c == *valids)
			return (1);
		valids++;
	}
	return (0);
}

void	set_build(t_flags *b)
{
	b->a = 0;
	b->l = 0;
	b->R = 0;
	b->r = 0;
	b->t = 0;
}

// checks if flag is lRrat and sets its value to be 1
static void	set_flag(char c, t_flags *b)
{
	ft_printf("im here to set the flag. %c\n", c);
	if (c == 'l')
		b->l = 1;
	if (c == 'R')
		b->R = 1;
	if (c == 'r')
		b->r = 1;
	if (c == 'a')
		b->a = 1;
	if (c == 't')
		b->t = 1;
}
static void	ls_parser(char *str, t_flags *b)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i++] == '-')
		{
			while (str[i] && is_valid_char(str[i]) == 1)
			{
				set_flag(str[i], b);
				i++;
			}
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_flags *build;
	DIR *d;
	struct dirent *dir;

	build = (t_flags *)malloc(sizeof(t_flags));
	if (!build)
		exit(-1);
	set_build(build);
	ls_parser(argv[1], build);
	// d = opendir(".");
	// if (d)
	// {
	// 	while ((dir = readdir(d)) != NULL)
	// 	{
	// 		ft_printf("%s\n", dir->d_name);
	// 	}
	// 	closedir(d);
	// }
	return (0);
}
