/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:10:47 by amann             #+#    #+#             */
/*   Updated: 2022/03/16 20:24:35 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	check_flags(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		ft_printf(argv[i]);
		ft_putchar('\n');
		i++;
	}
}

void	initialise_flags(t_ls **flags)
{
	*flags = (t_ls *) malloc(sizeof(t_ls));
	if (!(*flags))
		return ;
	(*flags)->list = FALSE;
	(*flags)->recursive = FALSE;
	(*flags)->reverse = FALSE;
	(*flags)->all = FALSE;
	(*flags)->time = FALSE;
}
