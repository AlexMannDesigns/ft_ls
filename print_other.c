/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:08:45 by amann             #+#    #+#             */
/*   Updated: 2022/04/04 17:44:26 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	print_nl_and_reset(size_t *line_len)
{
	ft_printf("\n");
	*line_len = 0;
}

static int	check_space(size_t line_len, t_file_info *current, size_t width)
{
	if ((line_len + ft_strlen(current->name)) < width - 4)
		return (TRUE);
	return (FALSE);
}

void	print_other(t_list *lst, char type)
{
	t_file_info		*current;
	size_t			line_len;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	line_len = 0;
	while (lst)
	{
		current = (t_file_info *) lst->content;
		if (type == ',' && line_len && check_space(line_len, current, w.ws_col))
			line_len += ft_printf(" ");
		else if (type == ',' && line_len)
			print_nl_and_reset(&line_len);
		if (!lst->next && type == ',')
		{
			line_len += ft_printf("%s\n", current->name);
			break ;
		}
		line_len += ft_printf("%s%c", current->name, type);
		lst = lst->next;
	}
}
