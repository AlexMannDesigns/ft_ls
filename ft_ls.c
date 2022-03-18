/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:39:01 by amann             #+#    #+#             */
/*   Updated: 2022/03/18 13:56:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

//#include <sys/ioctl.h>
//ft_printf("ft_ls: %s: No such file or directory\n", argv[i]);

int	main(int argc, char **argv)
{
	t_ls	*flags;
	char	**file_arr;
//	struct winsize w;
//    ioctl(0, TIOCGWINSZ, &w);
//
//    printf ("lines %d\n", w.ws_row);
//    printf ("columns %d\n", w.ws_col);
	if (argc == 1)
	{
		basic_display(FALSE);
		return (0);
	}
	flags = NULL;
	initialise_flags(&flags);
	if (!flags)
		return (1);
	if (!option_control(&argv, &flags))
		return (1);
	if (*argv)
		file_arr = directory_control(argv, flags);		
	else if (!flags->list)             		
		basic_display(flags->all);

	return (0);
}
