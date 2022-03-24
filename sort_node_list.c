/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_node_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:02:23 by amann             #+#    #+#             */
/*   Updated: 2022/03/24 18:03:26 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	node_list_swap(t_list **list, t_list **head)
{
	t_list	*b;
	t_list	*c;
	t_list	*temp;

	b = (*list)->next;
	c = (*list)->next->next;
	(*list)->next->next = *list;
	(*list)->next = c;
	if (*list == *head)
	{
		*head = b;
		return ;
	}
	temp = *head;
	while ((*head)->next != *list)
		*head = (*head)->next;
	(*head)->next = b;
	*head = temp;
	*list = *head;
}


void	sort_node_list(t_list **list, t_ls *flags)
{
	t_list	*head;
	char	*current_str;
	char	*next_str;

	head = *list;
	while ((*list)->next)
	{
		current_str = ((t_file_info *)(*list)->content)->name;
		next_str = ((t_file_info *)(*list)->next->content)->name;
	//	ft_printf("current %s || next %s\n", current_str, next_str);
		if (!flags->reverse && ft_strcmp(current_str, next_str) > 0)
			node_list_swap(list, &head);
		else if (flags->reverse && ft_strcmp(current_str, next_str) < 0)
			node_list_swap(list, &head);
		else
			*list = (*list)->next;
	}
	*list = head; //reset list pointer to the start
}
