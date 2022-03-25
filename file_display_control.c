/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_display_control.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:44:21 by amann             #+#    #+#             */
/*   Updated: 2022/03/25 18:38:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	file_display_control(char **arr, t_ls *flags)
{
	//if we are printing files, first, we need to make a node list of those files
	t_list	*list;
	size_t	i;

	list = NULL;
	i = 0;
	while (arr[i])
	{
		list_const_helper(arr[i], "./", &list);		
		i++;
	}
	if (flags->list)
		print_list(list, i, FALSE);
//free the node list
//the file array is freed in validate_array.c
}
