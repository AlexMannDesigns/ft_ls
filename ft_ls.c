/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:39:01 by amann             #+#    #+#             */
/*   Updated: 2022/04/05 16:57:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	display_loop(char **arr, t_ls *flags, unsigned int files_printed)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (arr[1] || files_printed)
			ft_printf("%s:\n", arr[i]);
		display_control(arr[i], flags);
		if (arr[i + 1])
			ft_putchar('\n');
		i++;
	}
}

static void	process_args(char **argv, t_ls *flags)
{
	char			**file_arr;
	unsigned int	files_printed;

	file_arr = NULL;
	files_printed = FALSE;
	flags->args_passed = TRUE;
	file_arr = directory_control(argv, flags, &files_printed);
	if (file_arr)
	{
		display_loop(file_arr, flags, files_printed);
		ft_freearray((void ***)&file_arr, check_arr_len((void **)file_arr));
	}
}

int	main(int argc, char **argv)
{
	t_ls			*flags;

	flags = NULL;
	initialise_flags(&flags);
	if (!flags)
		return (1);
	if (!option_control(&argv, &flags))
		return (1);
	if (argc == 1 || !*argv)
		display_control("./", flags);
	else if (*argv)
		process_args(argv, flags);
	free(flags);
	return (0);
}
