/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fields_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:02:11 by amann             #+#    #+#             */
/*   Updated: 2022/04/15 16:08:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static size_t	get_links(t_fields *width, t_file_info *n, size_t j)
{
	(width->links_arr)[j] = ft_itoa(n->links);
	width->blocks += n->blocks;
	return (ft_strlen((width->links_arr)[j]));
}

static size_t	get_username(t_fields *w, t_file_info *n, size_t j, t_ls *flg)
{
	char	*name;

	if (flg->group_no)
		(w->user_arr)[j] = ft_itoa(n->user);
	else
	{
		name = username(n->user);
		if (name)
			(w->user_arr)[j] = ft_strdup(name);
		else
			(w->user_arr)[j] = ft_itoa(n->user);
	}
	return (ft_strlen((w->user_arr)[j]));
}

static size_t	get_grp_id(t_fields *w, t_file_info *n, size_t j, t_ls *flg)
{
	char	*name;

	if (flg->group_no)
		(w->group_arr)[j] = ft_itoa(n->group);
	else
	{
		name = group_id(n->group);
		if (name)
			(w->group_arr)[j] = ft_strdup(name);
		else
			(w->group_arr)[j] = ft_itoa(n->group);
	}
	return (ft_strlen((w->group_arr)[j]));
}

static size_t	get_size(t_fields *width, t_file_info *n, size_t j)
{
	(width->size_arr)[j] = ft_itoa_base(n->size, 10);
	return (ft_strlen((width->size_arr)[j]));
}

void	init_fields_loop(t_list *list, t_fields *width, t_ls *flg, size_t *w_a)
{
	t_file_info	*n;
	size_t		j;
	static int	i;

	if (i > 3)
		i = 0;
	j = 0;
	while (list)
	{
		n = (t_file_info *)list->content;
		if (i == 0)
			w_a[j] = get_links(width, n, j);
		if (i == 1)
			w_a[j] = get_username(width, n, j, flg);
		if (i == 2)
			w_a[j] = get_grp_id(width, n, j, flg);
		if (i == 3 && n->type != BLK && n->type != CHR)
			w_a[j] = get_size(width, n, j);
		else if (i == 3 && (n->type == BLK || n->type == CHR))
			w_a[j] = 8;
		list = list->next;
		j++;
	}
	i++;
}
