/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:18:06 by amann             #+#    #+#             */
/*   Updated: 2022/03/29 16:21:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	display_recursion(t_file_info *current, t_ls *flags)
{
	ft_putchar('\n');
	if (!flags->args_passed)
		ft_printf("./");
	ft_printf("%s:\n", current->path);
	display_control(current->path, flags);			
}

void	display_control(char *dir, t_ls *flags)
{
	t_list			*file_list;
	t_file_info		*current;
	size_t			list_len;

	list_len = 0;
	file_list = list_constructor(dir, flags, &list_len);
	if (flags->list)
		print_list(file_list, list_len, TRUE);
	else
		print_basic(file_list);
	if (flags->recursive)
	{
		while (file_list)
		{
			current = (t_file_info *)file_list->content;
			if (current->type == DRC)
				display_recursion(current, flags);
			file_list = file_list->next;
		}
	}
	//NB free up the node list here
}
