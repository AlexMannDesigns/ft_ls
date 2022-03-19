/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:18:06 by amann             #+#    #+#             */
/*   Updated: 2022/03/19 15:45:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static DIR	*open_directory(char *dir_name)
{
	DIR	*directory;

	directory = opendir(dir_name);
	if (!directory)
	{
		ft_printf("there was an error\n");
		return (NULL);
	}
	return (directory);
}

static size_t	get_arr_len(int all, char *dir_name)
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

static void	populate_array(char **arr, char *dir_name, int all)
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

void	basic_display(char *dir_name, int all)
{
	char	**arr;
	size_t	len;

	len = get_arr_len(all, dir_name);
	//ft_printf("%zu\n", len);
	if (!len)
		return ;
	arr = (char **) ft_memalloc(sizeof(char *) * (len + 1));
	if (!arr)
		return ;
	populate_array(arr, dir_name, all);
	sort_arr(&arr);
	//ft_putendl("here");
	
	print_basic(arr);
	ft_freearray((void ***)&arr, len);
}
