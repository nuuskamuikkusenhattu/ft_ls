/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:22:12 by spuustin          #+#    #+#             */
/*   Updated: 2022/07/12 19:01:15 by spuustin         ###   ########.fr       */
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
-t = sort by time modified (most recently modified first) before sorting
the operands by lexicographical order.
*/

#include "ft_ls.h"

// sets all values of a struct to be 0 by default

static void set_build(t_ls *build)
{
	build->file_list = (char **)malloc(sizeof(char *) * 32000);
	if (!build->file_list)
		exit(1);
	build->file_count = 0;
	build->dir_list = (char **)malloc(sizeof(char *) * 32000);
	if (!build->dir_list)
		exit(1);
	build->dir_count = 0;
	build->non_exists = (char **)malloc(sizeof(char *) * 32000);
	if (!build->non_exists)
		exit(1);
	build->ne_count = 0;
	build->a = 0;
	build->l = 0;
	build->t = 0;
	build->r = 0;
	build->R = 0;
	build->flagsParsed = 0;
	build->flag_args = 0;
	build->path = ".";
}

int main(int argc, char **argv)
{
	t_ls *build;

	build = (t_ls *)malloc(sizeof(t_ls));
	if (!build)
		exit(1);
	set_build(build);
	if (argc > 1)
	{
		parser(argc, argv, build);
		create_lists(argv, build);
		//test_show_params(build); /debug
		print_all(build);
		//print_list(build);
	}
	if (argc == 1 || (build->flag_args == argc - 1))
	{
		list_all_in_current_dir(build, ".");
		sort(build);
		print_all(build);
	}
	exit(0);
}
