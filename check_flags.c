/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:10:47 by amann             #+#    #+#             */
/*   Updated: 2022/04/04 16:56:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/* 
 * Flags parsed after a directory name are ignored 
 * error message displayed if dir name not recognised
 * usage displayed if invalid flag parsed
*/

static int	flag_control(char *s, char *error, t_ls **flags)
{
	s++;
	if (*s == '\0')
		return (0);
	if (!ft_strchr(FLAGS, *s))
	{
		*error = *s;
		return (1);
	}
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
	else if (*s == '1')
		(*flags)->one = TRUE;
	else if (*s == 'm')
		(*flags)->comma = TRUE;
	else if (*s == 'n')
		(*flags)->group_no = TRUE;
	return (flag_control(s, error, flags));
}

int	option_control(char ***argv, t_ls **flags)
{
	char error;

	(*argv)++;
	while (**argv)
	{
		if ((**argv)[0] == '-')
		{
			if ((**argv)[1] == '\0')
				break ;
			if (flag_control(**argv, &error, flags))
			{	
				ft_printf("ft_ls: illegal option -- %c\n%s\n", error, USAGE);
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
	(*flags)->one = FALSE;
	(*flags)->comma = FALSE;
	(*flags)->group_no = FALSE;
	(*flags)->args_passed = FALSE;
}
