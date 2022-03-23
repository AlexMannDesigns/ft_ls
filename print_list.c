/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:39 by amann             #+#    #+#             */
/*   Updated: 2022/03/23 14:54:39 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*create_file_path(char *name, char *path, unsigned int list)
{
	char	*res;
	char	*temp;

	if (list && ft_strcmp(path, "./") == 0)
		return (ft_strdup(name));
	if (list || ft_strcmp(path, "./"))
		temp = ft_strjoin(path, "/");
	else
		temp = ft_strdup(path);
	res = ft_strjoin(temp, name);
	free(temp);
	return (res);
}	

void	handle_lnk_usr_grp_size(t_fields field_width, size_t i)
{
	ft_printf("%*s", field_width.links, (field_width.links_arr)[i]);
	ft_printf("%*s", field_width.user, (field_width.user_arr)[i]);
	ft_printf("%*s", field_width.group, (field_width.group_arr)[i]);
	ft_printf("%*s", field_width.size, (field_width.size_arr)[i]);
}

void	handle_time(char *time)
{
	char	*res;

	//remember, year is displayed instead of time with older files
	res = ft_strsub(time, 4, 12);
	ft_printf("%13s", res);
	free(res);
}

char	*get_linked_filename(char *file_path, char *path)
{
	struct stat		stat_data;
	DIR				*directory;
	struct dirent	*file;
	ino_t			file_serial;

	stat(file_path, &stat_data);
	directory = opendir(path);
	file = readdir(directory);
	while (file)
	{
		file_serial = file->d_ino;
		if (file_serial == stat_data.st_ino)
		{	
			closedir(directory);
			return (file->d_name);
		}
		file = readdir(directory);	
	}
	closedir(directory);
	return ("Unknown");
}
//function will also have to print individual files
//separate functions called in loop to a control function which can be called
//with the file path parsed

void	print_list(char **arr, char *path, unsigned int is_dir, size_t len)
{
	struct stat	stat_data;
	size_t		i;
	char		*file_path;
	t_fields	field_width;

	init_fields(&field_width, arr, path, len);
	if (is_dir)                                                                	
		ft_printf("total %lld\n", field_width.blocks); //add memory blocks here	
	//ft_printf("links: %zu, user: %zu, group: %zu, size: %zu\n", field_width.links, field_width.user, field_width.group, field_width.size);
	//ft_printf("%zu\n", len);
	i = 0;
	while (arr[i])
	{
		file_path = create_file_path(arr[i], path, TRUE);
		lstat(file_path, &stat_data);
		handle_permissions_and_type(stat_data.st_mode);
		handle_lnk_usr_grp_size(field_width, i);
		handle_time(ctime(&stat_data.st_mtime));
		ft_printf(" %s", arr[i]);
		if (S_ISLNK(stat_data.st_mode))
		   	ft_printf(" -> %s", get_linked_filename(file_path, path));	
		ft_putchar('\n');
		//ft_printf("\t%s\n", file_path);
		ft_memdel((void **)&file_path);
		i++;
	}
	//free char arrays in struct
	ft_freearray((void ***)&(field_width.links_arr), len - 1);
	ft_freearray((void ***)&(field_width.user_arr), len - 1);
	ft_freearray((void ***)&(field_width.group_arr), len - 1);
	ft_freearray((void ***)&(field_width.size_arr), len - 1);
}
