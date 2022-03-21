/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:39:01 by amann             #+#    #+#             */
/*   Updated: 2022/03/21 16:10:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

//#include <sys/ioctl.h>
//ft_printf("ft_ls: %s: No such file or directory\n", argv[i]);

static void	display_loop(char **arr, t_ls *flags)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (arr[1])
			ft_printf("%s:\n", arr[i]);
		display_control(arr[i], flags);
		if (arr[i + 1])
			ft_putchar('\n');
		i++;	
	}
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
	flags = NULL;
	initialise_flags(&flags);
	if (!flags)
		return (1);
	if (argc == 1)
	{
		display_control("./", flags);
		free(flags);
		return (0);
	}
	file_arr = NULL;
	if (!option_control(&argv, &flags))
		return (1);
	if (*argv)
	{
		//ft_putendl(*argv);
		file_arr = directory_control(argv, flags);		
		display_loop(file_arr, flags);	
	}
	else          		
		display_control("./", flags);
	if (file_arr)
		ft_freearray((void ***)&file_arr, check_arr_len((void **)file_arr));
	free(flags);
	return (0);
}
