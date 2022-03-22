/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:18:06 by amann             #+#    #+#             */
/*   Updated: 2022/03/22 12:42:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static DIR	*open_directory(char *dir_name)
{
	DIR	*directory;

//	ft_printf("dir name: %s\n", dir_name);
	directory = opendir(dir_name);
	if (!directory)
	{
		ft_printf("there was an error\n");
		return (NULL);
	}
	return (directory);
}

static size_t	get_arr_len(unsigned int all, char *dir_name)
{
	DIR				*directory;
	struct dirent	*next_filename;
	char			*name;
	size_t			len;

	directory = open_directory(dir_name);
	if (!directory)
		return (0);
	len = 0;
	next_filename = readdir(directory);
	while (next_filename)
	{
		name = next_filename->d_name;
		if (!all && (name[0] != '.'))
			len++;
		else if (all)
			len++;
		next_filename = readdir(directory);
	}
	closedir(directory);
	return (len);
}

static void	populate_array(char **arr, char *dir_name, unsigned int all)
{
	DIR				*directory;
	struct dirent	*next_filename;
	char			*name;
	size_t			i;

	directory = open_directory(dir_name);
	if (!directory)
		return ;
	i = 0;
	next_filename = readdir(directory);
	while (next_filename)
	{
		name = next_filename->d_name;
		if (!all && (name[0] != '.'))
			arr[i++] = ft_strdup(name);
		else if (all)
			arr[i++] = ft_strdup(name);
		next_filename = readdir(directory);
	}
	closedir(directory);
}

static void	sort_and_print(char *dir_name, t_ls *flags)
{
	char	**arr;
	size_t	len;
	//char	*next_dir;

	len = get_arr_len(flags->all, dir_name);
	//ft_printf("%zu\n", len);
	if (!len)
		return ;
	arr = (char **) ft_memalloc(sizeof(char *) * (len + 1));
	if (!arr)
		return ;
	populate_array(arr, dir_name, flags->all);
	sort_arr(&arr);
	//ft_putendl("here");
	if (flags->list)
		print_list(arr, dir_name);
	else
		print_basic(arr);
	ft_freearray((void ***)&arr, len);
}

void static	recursion_handler(char *file_path, t_ls *flags)
{
	ft_printf("\n%s:\n", file_path);
	display_control(file_path, flags);
}

void	display_control(char *dir, t_ls *flags)
{
	DIR				*directory;
	struct dirent	*next_filename;
	char			*file_name;
	char			*file_path;
	struct stat		stat_data;

	sort_and_print(dir, flags);
//check R flag
	if (flags->recursive)
	{
		directory = open_directory(dir);
		next_filename = readdir(directory);
		while (next_filename)
		{
			file_name = next_filename->d_name;
			file_path = create_file_path(file_name, dir, FALSE);
			stat(file_path, &stat_data);
			if (!flags->all && (file_name[0] != '.') && S_ISDIR(stat_data.st_mode))
				recursion_handler(file_path, flags);
			else if (flags->all && S_ISDIR(stat_data.st_mode))
				recursion_handler(file_path, flags);
			next_filename = readdir(directory);		
		}
		closedir(directory);
	}
}
