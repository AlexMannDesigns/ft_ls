/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_fields.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:27:08 by amann             #+#    #+#             */
/*   Updated: 2022/07/29 13:21:49 by amann            ###   ########.fr       */
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
		f_width->user = max + 1;
	if (col == 2)
		f_width->group = max;
	if (col == 3)
		f_width->size = max;
}

void	init_fields(t_fields *f_width, t_list *list, size_t len, t_ls *flags)
{
	size_t		i;
	size_t		*w_arr;

	w_arr = (size_t *) ft_memalloc(sizeof(size_t) * len);
	f_width->links_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->user_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->group_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->size_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->blocks = 0;
	//malloc protection needed here
	i = 0;
	while (i < 4)
	{
		init_fields_loop(list, f_width, flags, w_arr);
		max_width(f_width, w_arr, i, len);
		i++;
	}
	free(w_arr);
}
