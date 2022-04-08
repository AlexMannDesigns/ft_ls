/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:19:47 by amann             #+#    #+#             */
/*   Updated: 2022/04/08 18:04:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

size_t	set_col_width(t_list *lst)
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
	if (max > 6)
		return (max);
	else
		return (6);
}

size_t	set_col_number(size_t col_width)
{
	struct winsize	w;
	size_t			res;
	ioctl(0, TIOCGWINSZ, &w);
	
	res = w.ws_col / col_width;
	if (res > 1)
		return (res);
	else
		return (1);
}

size_t	set_col_height(size_t col_number, size_t len)
{
	if (len % col_number == 0)
		return (len / col_number);
	else
		return ((len / col_number) + 1);
}
