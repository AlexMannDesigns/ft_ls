/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:41:35 by amann             #+#    #+#             */
/*   Updated: 2022/03/25 18:29:58 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	trim_valid_arr(char ***arr, ssize_t len, ssize_t count)
{
	char	**new_arr;
	ssize_t	orig_len;

//	ft_printf("count: %zu  len: %zu\n", count, len);
	orig_len = len;
	new_arr = (char **) ft_memalloc(sizeof(char *) * (count + 1));
	if (!new_arr)
	{
		ft_freearray((void ***)arr, len);
		return ;
	}
	while (len >= 0)
	{
//		ft_printf("count: %zu  len: %zu\n", count, len);
//		ft_putendl((*arr)[len]);
		if ((*arr)[len])
		{
			count--;
			new_arr[count] = ft_strdup((*arr)[len]);
			if (!new_arr[count])
			{
				ft_freearray((void ***)arr, orig_len);
				return ;
			}
		}
		len--;
	}
	ft_freearray((void ***)arr, orig_len);
	(*arr) = new_arr;
}

static char	**set_files_and_links(char ***arr, size_t fil_len, size_t arr_len)
{
	char 			**file_arr;
	size_t			i;
	size_t			j;
	struct stat		stat_data;
	unsigned int	type;

	//ft_printf("fil %zu arr %zu\n", fil_len, arr_len);
	file_arr = (char **) ft_memalloc(sizeof(char *) * (fil_len + 1));
	if (!file_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < arr_len)
	{
		if ((*arr)[i])
		{
			stat((*arr)[i], &stat_data);
			type = check_file_type(stat_data.st_mode);
	   		//ft_printf("type = %u\n", type);
			if (type && type != DRC)
			{	
				file_arr[j] = ft_strdup((*arr)[i]);
				ft_memdel((void **)&((*arr)[i]));
			//	ft_printf("file_arr idx %zu = %s\n", j, file_arr[j]);			
				j++;
			}
		}
		i++;
	}
	return (file_arr);
}

static void	validate_arr_loop(char ***arr, ssize_t *len, ssize_t *d_c, size_t *f_c)
{
	struct stat		stat_data;
	unsigned int	type;

	while ((*arr)[*len])
	{
//		ft_printf("%zu %s\n", len, (*arr)[len]);
//		current = opendir((*arr)[len]);
		if (stat((*arr)[*len], &stat_data))
		{
			ft_printf("ft_ls: %s: No such file or directory\n", (*arr)[*len]);
			ft_memdel((void **)&((*arr)[*len]));	
		}
		else
		{
			type = check_file_type(stat_data.st_mode);
			if (type == DRC)
				(*d_c)++;
			else
				(*f_c)++;	//	ft_putendl((*arr)[len]);	
		}
		(*len)++;
	}
}

void	validate_arr(char ***arr, t_ls *flags, unsigned int *files_printed)
{
	ssize_t			len;
	ssize_t			dir_count;
	size_t			fil_count;
	char			**files_and_links;
	
	len = 0; 
	fil_count = 0;
	dir_count = 0;
	validate_arr_loop(arr, &len, &dir_count, &fil_count);
	if (fil_count)
	{
		files_and_links = set_files_and_links(arr, fil_count, len);
		if (flags->list)
		{
			file_display_control(files_and_links, flags);
		}
		//else
	//		print_basic(files_and_links);
		//print_files_and_links(files_and_links);
		//ft_putendl("hello");
		ft_freearray((void ***)&files_and_links, fil_count);
		if (dir_count)
			ft_putchar('\n');
	}
	if (len > dir_count)
	{
		*files_printed = TRUE;
		trim_valid_arr(arr, len, dir_count);
	}
}

