/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_display_control.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:44:21 by amann             #+#    #+#             */
/*   Updated: 2022/03/31 17:00:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	file_display_control(char **arr, t_ls *flags)
{
	t_list	*list;
	t_list	*head;
	size_t	i;

	sort_arr(&arr, flags, FALSE);
	list = NULL;
	i = 0;
	while (arr[i])
	{
		list_const_helper(arr[i], "./", &list);
		i++;
	}
	sort_node_list(&list, flags);
	head = list;
	if (flags->list)
		print_list(list, i, FALSE);
	else
		print_basic(list);
	ft_lstdel(&head, &free_info_struct);
}
