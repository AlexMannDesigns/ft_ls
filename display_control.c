/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:18:06 by amann             #+#    #+#             */
/*   Updated: 2022/03/25 19:03:01 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

//static void	recursion_handler(char *file_path, t_ls *flags)
//{
//	ft_printf("\n%s:\n", file_path);
//	display_control(file_path, flags);
//}

void	display_control(char *dir, t_ls *flags)
{
//	DIR				*directory;
//	struct dirent	*next_filename;
//	char			*file_name;
//	char			*file_path;
//	struct stat		stat_data;
	t_list			*file_list;
	t_file_info		*current;

	size_t			list_len;

	list_len = 0;
	file_list = list_constructor(dir, flags, &list_len);
	if (flags->list)
		print_list(file_list, list_len, TRUE);
	//	else
//		print_nodes_basic(file_list);
	if (flags->recursive)
	{
	//	directory = opendir(dir);
	//	next_filename = readdir(directory);
		while (file_list)
		{
			//file_name = next_filename->d_name;
			//file_path = create_file_path(file_name, dir, FALSE);
			//stat(file_path, &stat_data);
			//if (!flags->all && (file_name[0] != '.') && S_ISDIR(stat_data.st_mode))
			//	recursion_handler(file_path, flags);
			//else if (flags->all && S_ISDIR(stat_data.st_mode))
			//	recursion_handler(file_path, flags);
			//next_filename = readdir(directory);		
			current = (t_file_info *)file_list->content;
			if (current->type == DRC)
			{
				ft_printf("\n%s:\n", current->path);
				display_control(current->path, flags);			
			}
			file_list = file_list->next;
			//ft_putendl(current->);
		}
		//closedir(directory);
	}
	//NB free up the node list here
}
