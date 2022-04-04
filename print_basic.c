/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:14:55 by amann             #+#    #+#             */
/*   Updated: 2022/04/04 18:12:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	print_object(t_list *lst, size_t *len, size_t col_width)
{
	t_file_info	*current;

	current = (t_file_info *) lst->content;
	ft_printf("%-*s", col_width, current->name);
	(*len)--;
}

static void	print_nl(t_list **lst, t_list *head, size_t *col, size_t *row)
{
	size_t			j;

	ft_putchar('\n');
	*lst = head;
	*col = 0;
	j = 0;
	while (j < *row)
	{
		*lst = (*lst)->next;
		j++;
	}
	(*row)++;
}

static void	next_object(t_list **lst, size_t col_height)
{
	size_t	i;

	i = 0;
	while (i < col_height && *lst)
	{
		*lst = (*lst)->next;
		i++;
	}
}

void	print_basic(t_list *lst, size_t len)
{
	t_list		*head;
	t_columns	col_data;
	size_t		row;
	size_t		col;

	col_data.col_width = set_col_width(lst) + 2;
	col_data.col_number = set_col_number(col_data.col_width);
	col_data.col_height = set_col_height(col_data.col_number, len);
	col = 1;
	head = lst;
	row = 1;
	while (len)
	{
		if (lst)
			print_object(lst, &len, col_data.col_width);
		if (col % col_data.col_number == 0)
			print_nl(&lst, head, &col, &row);
		else
			next_object(&lst, col_data.col_height);
		col++;
	}
	lst = head;
	ft_putchar('\n');
}
