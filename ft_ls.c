/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:39:01 by amann             #+#    #+#             */
/*   Updated: 2022/03/17 16:28:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

//ft_printf("ft_ls: %s: No such file or directory\n", argv[i]);

int	main(int argc, char **argv)
{
	t_ls	*flags;
	
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
		ft_printf("%s\n", *argv);
	basic_display(flags->all);
	return (0);
}
