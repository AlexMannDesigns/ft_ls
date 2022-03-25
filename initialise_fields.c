/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_fields.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:27:08 by amann             #+#    #+#             */
/*   Updated: 2022/03/25 16:53:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*username(uid_t st_uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(st_uid);
	if (pwd)
		return (pwd->pw_name);
	return ("Unkown");
}

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
	size_t		j;
	size_t		*w_arr;
	t_list		*head;
	t_file_info	*node;

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
		j = 0;
		while (list)
		{
			node = (t_file_info *)list->content;
			if (i == 0)
			{
				(f_width->links_arr)[j] = ft_itoa(node->links);
				w_arr[j] = ft_strlen((f_width->links_arr)[j]);
           	 	f_width->blocks += node->blocks;
			}
			if (i == 1)
            {
            	(f_width->user_arr)[j] = ft_strdup(username(node->user));
            	w_arr[j] = ft_strlen((f_width->user_arr)[j]);
            }
			if (i == 2)
           	{
           		(f_width->group_arr)[j] = ft_itoa(node->group);
           		w_arr[j] = ft_strlen((f_width->group_arr)[j]);
           	}
			if (i == 3)                                        	
		   	{                                               	
		   		(f_width->size_arr)[j] = ft_itoa_base(node->size, 10);	
		   		w_arr[j] = ft_strlen((f_width->size_arr)[j]);	
		   	}                                               	
			list = list->next;
			j++;
		}
		max_width(f_width, w_arr, i, len);
		i++;
		list = head;	
	}
	free(w_arr);
}              
