/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:14:55 by amann             #+#    #+#             */
/*   Updated: 2022/03/18 11:43:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static size_t	set_col_width(char **arr)
{
	size_t	max;
	size_t	current_len;
	size_t	i;

	max = 0;
	i = 0;
	while (arr[i])
	{
		current_len = ft_strlen(arr[i]);
		if (current_len > max)
			max = current_len;
		i++;
	}
	return (max);
}

static size_t	set_col_number(size_t col_width)
{
	if (col_width > 30)
		return (1);
	else
		return (5);
}

void	print_basic(char **arr)
{
	size_t i;
	size_t count;
	size_t col_width;
	size_t col_number;

	col_width = set_col_width(arr) + 1;
	col_number = set_col_number(col_width);
	i = 0;
	count = 1;
	while (arr[i])
	{
		ft_printf("%-*s", col_width, arr[i]);
		if (count % col_number == 0)
				ft_putchar('\n');
		i++;
		count++;
	}
	ft_putchar('\n');	
}
