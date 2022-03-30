/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:18:06 by amann             #+#    #+#             */
/*   Updated: 2022/03/30 16:43:45 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	print_error(char *dir)
{
	char 	*res;
	int		len;

	len = ft_strlen(dir);
	while (len > 0 && dir[len] != '/')
		len--;
	res = ft_strdup(dir + len + 1);
	ft_printf("ft_ls: %s: Permission denied\n", res);
	free(res);
}

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
	t_list			*head;
	t_file_info		*current;
	unsigned int	error;
	size_t			list_len;

	list_len = 0;
	error = FALSE;
	file_list = list_constructor(dir, flags, &list_len, &error);
	head = file_list;
	if (file_list && flags->list)
		print_list(file_list, list_len, TRUE);
	else if (file_list)
		print_basic(file_list);
	if (error)
		print_error(dir);
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
	ft_lstdel(&head, &free_info_struct);
}
