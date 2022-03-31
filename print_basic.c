/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:14:55 by amann             #+#    #+#             */
/*   Updated: 2022/03/31 15:25:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static size_t	set_col_width(t_list *lst)
{
	t_file_info	*current;
	size_t		max;
	size_t		current_len;
	t_list		*head;

	max = 0;
	head = lst;
	while (lst)
	{
		current = (t_file_info *) lst->content;
		current_len = ft_strlen(current->name);
		if (current_len > max)
			max = current_len;
		lst = lst->next;
	}
	lst = head;
	return (max);
}

static size_t	set_col_number(size_t col_width)
{
	if (col_width > 50)
		return (1);
	else
		return (5);
}

void	print_basic(t_list *lst)
{
	t_list		*head;
	t_file_info	*current;
	size_t		count;
	size_t		col_width;
	size_t		col_number;

	col_width = set_col_width(lst) + 1;
	col_number = set_col_number(col_width);
	count = 1;
	head = lst;
	while (lst)
	{
		current = (t_file_info *) lst->content;
		ft_printf("%-*s", col_width, current->name);
		if (count % col_number == 0)
			ft_putchar('\n');
		lst = lst->next;
		count++;
	}
	lst = head;
	ft_putchar('\n');
}
