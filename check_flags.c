/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:10:47 by amann             #+#    #+#             */
/*   Updated: 2022/03/31 17:13:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/* 
 * Flags parsed after a directory name are ignored 
 * error message displayed if dir name not recognised
 * usage displayed if invalid flag parsed
*/

static int	flag_control(char *s, t_ls **flags)
{
	s++;
	if (*s == '\0')
		return (0);
	if (!ft_strchr(FLAGS, *s))
		return (1);
	if (*s == 'l')
		(*flags)->list = TRUE;
	else if (*s == 'R')
		(*flags)->recursive = TRUE;
	else if (*s == 'r')
		(*flags)->reverse = TRUE;
	else if (*s == 'a')
		(*flags)->all = TRUE;
	else if (*s == 't')
		(*flags)->time = TRUE;
	return (flag_control(s, flags));
}

int	option_control(char ***argv, t_ls **flags)
{
	(*argv)++;
	while (**argv)
	{
		if ((**argv)[0] == '-')
		{
			if ((**argv)[1] == '\0')
				break ;
			if (flag_control(**argv, flags))
			{	
				ft_printf("%s\n", USAGE);
				return (0);
			}
		}
		else
			break ;
		(*argv)++;
	}
	return (1);
}

void	initialise_flags(t_ls **flags)
{
	*flags = (t_ls *) ft_memalloc(sizeof(t_ls));
	if (!(*flags))
		return ;
	(*flags)->list = FALSE;
	(*flags)->recursive = FALSE;
	(*flags)->reverse = FALSE;
	(*flags)->all = FALSE;
	(*flags)->time = FALSE;
	(*flags)->args_passed = FALSE;
}
