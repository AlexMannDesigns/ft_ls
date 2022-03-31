/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fields_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:02:11 by amann             #+#    #+#             */
/*   Updated: 2022/03/31 16:57:00 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	get_links(t_fields *width, t_file_info *n, size_t *w_a, size_t j)
{
	(width->links_arr)[j] = ft_itoa(n->links);
	w_a[j] = ft_strlen((width->links_arr)[j]);
	width->blocks += n->blocks;
}

static void	get_username(t_fields *width, t_file_info *n, size_t *w_a, size_t j)
{
	(width->user_arr)[j] = ft_strdup(username(n->user));
	w_a[j] = ft_strlen((width->user_arr)[j]);
}

static void	get_group_id(t_fields *width, t_file_info *n, size_t *w_a, size_t j)
{
	(width->group_arr)[j] = ft_strdup(group_id(n->group));
	w_a[j] = ft_strlen((width->group_arr)[j]);
}

static void	get_size(t_fields *width, t_file_info *n, size_t *w_a, size_t j)
{
	(width->size_arr)[j] = ft_itoa_base(n->size, 10);
	w_a[j] = ft_strlen((width->size_arr)[j]);
}

void	init_fields_loop(t_list *list, t_fields *width, size_t *w_a, size_t i)
{
	t_file_info	*n;
	size_t		j;

	j = 0;
	while (list)
	{
		n = (t_file_info *)list->content;
		if (i == 0)
			get_links(width, n, w_a, j);
		if (i == 1)
			get_username(width, n, w_a, j);
		if (i == 2)
			get_group_id(width, n, w_a, j);
		if (i == 3)
			get_size(width, n, w_a, j);
		list = list->next;
		j++;
	}
}
