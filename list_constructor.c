/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:50:38 by amann             #+#    #+#             */
/*   Updated: 2022/08/08 14:47:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	list_const_helper(char *file_name, char *dir, t_list **file_list)
{
	t_file_info	*temp;

	temp = initialise_file_info(file_name, dir);
	if (!temp)
		return ;
	ft_lstadd_back(file_list, ft_lstnew((void *)temp, sizeof(t_file_info)));
	free(temp);
}

static t_list	*lc_loop(DIR *directory, size_t *l, char *dir, t_ls *flg)
{
	struct dirent	*next_filename;
	char			*name;
	t_list			*file_list;

	file_list = NULL;
	next_filename = readdir(directory);
	while (next_filename)
	{
		name = next_filename->d_name;
		if (!flg->all && name[0] != '.')
		{
			list_const_helper(name, dir, &file_list);
			*l += 1;
		}
		else if (flg->all)
		{
			list_const_helper(name, dir, &file_list);
			*l += 1;
		}
		next_filename = readdir(directory);
	}
	return (file_list);
}

t_list	*list_constructor(char *dir, t_ls *flg, size_t *l, unsigned int *err)
{
	t_list			*file_list;
	DIR				*directory;

	file_list = NULL;
	directory = opendir(dir);
	if (!directory)
	{
		*err = TRUE;
		return (file_list);
	}
	file_list = lc_loop(directory, l, dir, flg);
	if (*l)
		sort_node_list(&file_list, flg);
	closedir(directory);
	return (file_list);
}
