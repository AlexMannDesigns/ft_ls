/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_node_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:02:23 by amann             #+#    #+#             */
/*   Updated: 2022/04/07 16:31:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void static	update_original(t_list **lst, t_list *min)
{
	t_list	*head;

	head = *lst;
	if (*lst == min)
	{
		*lst = (*lst)->next;
		return ;
	}
	while ((*lst)->next != min)
		*lst = (*lst)->next;
	(*lst)->next = (*lst)->next->next;
	*lst = head;
}

void static	update_sorted(t_list **sorted, t_list *min)
{
	t_list	*head;

	head = *sorted;
	if (!(*sorted))
		*sorted = min;
	else
	{
		while ((*sorted)->next)
			*sorted = (*sorted)->next;
		(*sorted)->next = min;
		*sorted = head;
	}
}

static t_list	*selection_sort_control(t_list **lst, t_ls *flags)
{
	t_list		*min;
	t_file_info	*current;
	t_file_info	*min_info;

	min = NULL;
	while (*lst)
	{
		current = (t_file_info *)(*lst)->content;
		if (min)
		{
			min_info = (t_file_info *) min->content;
			if (standard_lexico(min_info, current, flags))
				min = *lst;
			else if (reverse_lexico(min_info, current, flags))
				min = *lst;
			else if (standard_time(min_info, current, flags))
				min = *lst;
			else if (reverse_time(min_info, current, flags))
				min = *lst;
		}
		else
			min = *lst;
		*lst = (*lst)->next;
	}
	return (min);
}

void	sort_node_list(t_list **lst, t_ls *flags)
{
	t_list	*sorted;
	t_list	*head;
	t_list	*min;

	sorted = NULL;
	min = NULL;
	head = *lst;
	while (*lst)
	{
		min = selection_sort_control(lst, flags);
		*lst = head;
		update_sorted(&sorted, min);
		update_original(lst, min);
		head = *lst;
		min->next = NULL;
		min = NULL;
	}
	*lst = sorted;
}
