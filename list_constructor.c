/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:50:38 by amann             #+#    #+#             */
/*   Updated: 2022/03/30 17:56:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	populate_file_info(t_file_info **info, char *file_name, char *dir)
{
	struct stat	stat_data;
	char		*file_path;
	char		buff[LS_BUF_SIZE + 1];
	ssize_t		len;	

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
	if ((*info)->type == LNK)
	{
		ft_bzero((void *) buff, LS_BUF_SIZE + 1);
		len = readlink(file_path, buff, LS_BUF_SIZE);
//		ft_printf("%zd\n", len);
		(*info)->links_to = ft_strndup(buff, len);	
	}
	else
		(*info)->links_to = NULL;
}

static t_file_info	*initialise_file_info(char *file_name, char *dir)
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

void	list_const_helper(char *file_name, char *dir, t_list **file_list)
{
	t_file_info	*temp;

	temp = initialise_file_info(file_name, dir);
	
	if (!temp)
		return ;
	ft_lstadd_back(file_list, ft_lstnew((void *)temp, sizeof(t_file_info)));
	free(temp);
}

t_list	*list_constructor(char *dir, t_ls *flags, size_t *len, unsigned int *error)
{
	t_list			*file_list;
	DIR				*directory;
	struct dirent	*next_filename;
	char			*name;    

	file_list = NULL;	
	directory = opendir(dir);
	if (!directory)
	{
		*error = TRUE;
		return (file_list);
	}
	//ft_printf("%zu\n", len);
//	ft_putendl("hello");
	next_filename = readdir(directory);
	while (next_filename)
	{
//		ft_putendl("here");
		name = next_filename->d_name;
		if (!flags->all && name[0] != '.')
		{
			list_const_helper(name, dir, &file_list);
			*len += 1;
		}
		else if (flags->all)
		{
			list_const_helper(name, dir, &file_list);
			*len += 1;	
		}
		next_filename = readdir(directory);		
	}
//	ft_printf("%zu\n", *len);
	if (*len)		
		sort_node_list(&file_list, flags);
	
//	ft_putendl("-------------");
//	while (file_list)
//	{
//		ft_putendl(((t_file_info *)file_list->content)->name);
//		file_list = file_list->next;	
//	}
//	ft_putendl("-------------");
	closedir(directory);
	return (file_list);
}
