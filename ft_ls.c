/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:39:01 by amann             #+#    #+#             */
/*   Updated: 2022/03/19 18:06:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

//#include <sys/ioctl.h>
//ft_printf("ft_ls: %s: No such file or directory\n", argv[i]);

static void	display_control(char **arr, t_ls *flags)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s:\n", arr[i]);
		basic_display(arr[i], flags->all);
		if (arr[i + 1])
			ft_putchar('\n');
		i++;	
	}
	flags->reverse = 1;
}

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
		basic_display("./" , FALSE);
		return (0);
	}
	file_arr = NULL;
	flags = NULL;
	initialise_flags(&flags);
	if (!flags)
		return (1);
	if (!option_control(&argv, &flags))
		return (1);
	if (*argv)
	{
		//ft_putendl(*argv);
		file_arr = directory_control(argv, flags);		
		display_control(file_arr, flags);
	}
	else if (!flags->list)             		
		basic_display("./", flags->all);
	if (file_arr)
		ft_freearray((void ***)&file_arr, check_arr_len((void **)file_arr));
	return (0);
}
