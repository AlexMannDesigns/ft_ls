/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_file_info.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:07 by amann             #+#    #+#             */
/*   Updated: 2022/03/31 16:38:30 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	populate_link_info(t_file_info **info, char *file_path)
{
	char	buff[LS_BUF_SIZE + 1];
	ssize_t	len;

	if ((*info)->type == LNK)
	{
		ft_bzero((void *) buff, LS_BUF_SIZE + 1);
		len = readlink(file_path, buff, LS_BUF_SIZE);
		if (len == -1)
		{
			(*info)->links_to = NULL;
			return ;
		}
		(*info)->links_to = ft_strndup(buff, len);
	}
	else
		(*info)->links_to = NULL;
}

static void	populate_file_info(t_file_info **info, char *file_name, char *dir)
{
	struct stat	stat_data;
	char		*file_path;
	char		buff[LS_BUF_SIZE + 1];

	file_path = create_file_path(file_name, dir, TRUE);
	if (!file_path)
		return ;
	lstat(file_path, &stat_data);
	(*info)->stats = stat_data;
	(*info)->type = check_file_type(stat_data.st_mode);
	(*info)->name = ft_strdup(file_name);
	(*info)->dir_name = ft_strdup(dir);
	(*info)->path = file_path;
	(*info)->user = stat_data.st_uid;
	(*info)->group = stat_data.st_gid;
	(*info)->modified = stat_data.st_mtime;
	(*info)->created = stat_data.st_ctime;
	(*info)->links = stat_data.st_nlink;
	(*info)->blocks = stat_data.st_blocks;
	(*info)->size = stat_data.st_size;
	(*info)->attr = listxattr(file_name, buff, LS_BUF_SIZE, XATTR_NOFOLLOW);
	populate_link_info(info, file_path);
}

t_file_info	*initialise_file_info(char *file_name, char *dir)
{
	t_file_info	*res;

	res = (t_file_info *) ft_memalloc(sizeof(t_file_info));
	if (!res)
		return (NULL);
	res->type = 0;
	res->name = NULL;
	res->dir_name = NULL;
	res->path = NULL;
	res->user = 0;
	res->group = 0;
	res->modified = 0;
	res->created = 0;
	res->links = 0;
	res->blocks = 0;
	res->size = 0;
	res->links_to = NULL;
	res->attr = 0;
	populate_file_info(&res, file_name, dir);
	if (!check_struct_malloc(&res))
		return (NULL);
	return (res);
}
