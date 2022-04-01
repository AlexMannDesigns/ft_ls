/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:41:35 by amann             #+#    #+#             */
/*   Updated: 2022/04/01 13:01:42 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	sfal_helper(char ***arr, char **file_arr, size_t *j, size_t i)
{
	struct stat		stat_data;
	unsigned int	type;

	stat((*arr)[i], &stat_data);
	type = check_file_type(stat_data.st_mode);
	if (type && type != DRC)
	{
		file_arr[*j] = ft_strdup((*arr)[i]);
		ft_memdel((void **)&((*arr)[i]));
		(*j)++;
	}
}

static char	**set_files_and_links(char ***arr, size_t fil_len, size_t arr_len)
{
	char			**file_arr;
	size_t			i;
	size_t			j;

	file_arr = (char **) ft_memalloc(sizeof(char *) * (fil_len + 1));
	if (!file_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < arr_len)
	{
		if ((*arr)[i])
			sfal_helper(arr, file_arr, &j, i);
		i++;
	}
	return (file_arr);
}

static void	va_loop(char ***arr, ssize_t *len, ssize_t *d_c, size_t *f_c)
{
	struct stat		stat_data;
	unsigned int	type;

	while ((*arr)[*len])
	{
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
				(*f_c)++;
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
	va_loop(arr, &len, &dir_count, &fil_count);
	if (fil_count)
	{
		files_and_links = set_files_and_links(arr, fil_count, len);
		file_display_control(files_and_links, flags);
		ft_freearray((void ***)&files_and_links, fil_count);
		if (dir_count)
			ft_putchar('\n');
		else
			ft_freearray((void ***)arr, fil_count);
	}
	if (*arr && len > dir_count)
	{
		*files_printed = TRUE;
		trim_valid_arr(arr, len, dir_count);
	}
}
