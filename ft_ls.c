/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:39:01 by amann             #+#    #+#             */
/*   Updated: 2022/03/16 20:20:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

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
	ft_putendl("here now");
	check_flags(argv + 1);
	return (0);
}
