/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:14:05 by amann             #+#    #+#             */
/*   Updated: 2022/03/30 18:02:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	free_info_struct(void *info, size_t content_size)
{
	t_file_info	*temp;

	temp = (t_file_info*) info;
	if (!content_size)
		return ;
	free(temp->name);
	free(temp->dir_name);
	free(temp->path);
	if (temp->links_to)
		free(temp->links_to);
	ft_memdel((void **)&temp);
//	ft_putendl("bonjour!");
}
