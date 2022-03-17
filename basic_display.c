/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:18:06 by amann             #+#    #+#             */
/*   Updated: 2022/03/17 15:56:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

size_t	get_arr_len(int all, char *dir_name)
{
	DIR				*directory;
	struct dirent	*next_filename;
	char			*name;
	size_t			len;
	
	directory = opendir(dir_name);
	if (!directory)
	{
		ft_printf("there was an error\n");
		return (0);
	}
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

void	populate_array(char **arr, char *dir_name, int all)
{
	DIR				*directory;
	struct dirent	*next_filename;
	char			*name;
	size_t			i;

	directory = opendir(dir_name);
	if (!directory)
	{
		ft_printf("there was an error\n");
		return ;
	}
	i = 0;
	next_filename = readdir(directory);
	while (next_filename)
	{
		name = next_filename->d_name;
		if (!all && (name[0] != '.'))
		{	
			arr[i] = ft_strdup(name);
			i++;
		}
		else if (all)
		{
			arr[i] = ft_strdup(name);
			i++;
		}
		next_filename = readdir(directory);
	}
	closedir(directory);
}

void	basic_display(int all)
{
	char			**arr;
	size_t			len;

	len = get_arr_len(all, "./");
	if (!len)
		return ;
	arr = (char **) malloc((sizeof(char *) * len) + 1);
	if (!arr)
		return ;
	arr[len] = NULL;
	populate_array(arr, "./", all);
	while (*arr)
	{
		ft_printf("%s\n", *arr);
		arr++;
	}
}
