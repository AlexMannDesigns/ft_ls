/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:32:56 by amann             #+#    #+#             */
/*   Updated: 2022/03/24 15:54:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	free_struct(t_file_info **info)
{
	if ((*info)->name)
		free((*info)->name);
	if ((*info)->dir_name)
		free((*info)->dir_name);
	if ((*info)->path)
		free((*info)->path);
	if ((*info)->links_to)
		free((*info)->links_to);
}

int	check_struct_malloc(t_file_info **info)
{
	if (!((*info)->name)) 
	{
		free_struct(info);
		return (0);
	}
	if (!((*info)->dir_name)) 
	{	
		free(info);
		return (0);
	}
	if (!((*info)->path)) 
	{	
		free_struct(info);
		return (0);
	}
	if ((*info)->type == LNK && !((*info)->links_to)) 
	{	
		free_struct(info);
		return (0);
	}
	return (1);
}

