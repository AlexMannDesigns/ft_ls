/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_fields.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:27:08 by amann             #+#    #+#             */
/*   Updated: 2022/03/31 16:42:30 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	max_width(t_fields *f_width, size_t *w_arr, size_t col, size_t len)
{
	size_t	i;
	size_t	max;

	max = 0;
	i = 0;
	while (i < len)
	{
		if (w_arr[i] > max)
			max = w_arr[i];
		i++;
	}
	max++;
	if (col == 0)
		f_width->links = max;
	if (col == 1)
		f_width->user = max;
	if (col == 2)
		f_width->group = max + 1;
	if (col == 3)
		f_width->size = max + 1;
}

void	init_fields(t_fields *f_width, t_list *list, size_t len)
{
	size_t		i;
	size_t		*w_arr;
	t_list		*head;

	i = 0;
	w_arr = (size_t *) ft_memalloc(sizeof(size_t) * len);
	f_width->links_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->user_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->group_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->size_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->blocks = 0;
	head = list;
	while (i < 4)
	{
		init_fields_loop(list, f_width, w_arr, i);
		max_width(f_width, w_arr, i, len);
		i++;
	}
	free(w_arr);
}
