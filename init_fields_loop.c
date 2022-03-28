/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fields_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:02:11 by amann             #+#    #+#             */
/*   Updated: 2022/03/28 13:04:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	get_links_and_blocks(t_fields *f_width, t_file_info *node, size_t *w_arr, size_t j)
{
	(f_width->links_arr)[j] = ft_itoa(node->links);
	w_arr[j] = ft_strlen((f_width->links_arr)[j]);
 	f_width->blocks += node->blocks;
}

static void	get_username(t_fields *f_width, t_file_info *node, size_t *w_arr, size_t j)
{
	(f_width->user_arr)[j] = ft_strdup(username(node->user));
	w_arr[j] = ft_strlen((f_width->user_arr)[j]);
}

static void	get_group_id(t_fields *f_width, t_file_info *node, size_t *w_arr, size_t j)
{
	(f_width->group_arr)[j] = ft_strdup(group_id(node->group));
	w_arr[j] = ft_strlen((f_width->group_arr)[j]);
}

static void	get_size(t_fields *f_width, t_file_info *node, size_t *w_arr, size_t j)
{                                               	
	(f_width->size_arr)[j] = ft_itoa_base(node->size, 10);	
	w_arr[j] = ft_strlen((f_width->size_arr)[j]);	
}                                               	

void	init_fields_loop(t_list *list, t_fields *f_width, size_t *w_arr, size_t i)
{
	t_file_info	*node;
	size_t		j;

	j = 0;
	while (list)
	{
		node = (t_file_info *)list->content;
		if (i == 0)
			get_links_and_blocks(f_width, node, w_arr, j);
		if (i == 1)
			get_username(f_width, node, w_arr, j);
		if (i == 2)
			get_group_id(f_width, node, w_arr, j);          	
		if (i == 3)                                        	
			get_size(f_width, node, w_arr, j);          	
		list = list->next;
		j++;
	}
}

