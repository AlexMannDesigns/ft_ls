/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_flag_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:08:20 by amann             #+#    #+#             */
/*   Updated: 2022/04/06 13:39:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	standard_lexico(t_file_info *c, t_file_info *n, t_ls *flags)
{
	if (!flags->reverse && !flags->time && ft_strcmp(c->name, n->name) > 0)
		return (TRUE);
	return (FALSE);
}

int	reverse_lexico(t_file_info *c, t_file_info *n, t_ls *flags)
{
	if (flags->reverse && !flags->time && ft_strcmp(c->name, n->name) < 0)
		return (TRUE);
	return (FALSE);
}

int	standard_time(t_file_info *c, t_file_info *n, t_ls *flags)
{
	if (!flags->reverse && flags->time && (c->modified < n->modified))
		return (TRUE);
	else if (!flags->reverse && flags->time && (c->modified == n->modified))
	{
		if (ft_strcmp(c->name, n->name) > 0)
			return (TRUE);
	}
	return (FALSE);
}

int	reverse_time(t_file_info *c, t_file_info *n, t_ls *flags)
{
	if (flags->reverse && flags->time && (c->modified > n->modified))
		return (TRUE);
	else if (flags->reverse && flags->time && (c->modified == n->modified))
	{
		if (ft_strcmp(c->name, n->name) < 0)
			return (TRUE);
	}
	return (FALSE);
}
