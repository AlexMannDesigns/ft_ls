/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:41:35 by amann             #+#    #+#             */
/*   Updated: 2022/04/19 12:34:41 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int	sfal_helper(char *str, char **file_arr, size_t *j, t_ls *flags)
{
	struct stat		stat_data;
	unsigned int	type;

	if (flags->list)
		lstat(str, &stat_data);
	else
		stat(str, &stat_data);
	type = check_file_type(stat_data.st_mode);
	if (type && type != DRC)
	{
		file_arr[*j] = ft_strdup(str);
		(*j)++;
		return (1);
	}
	return (0);
}

static char	**set_files_links(char ***arr, size_t flen, size_t alen, t_ls *flg)
{
	char			**file_arr;
	size_t			i;
	size_t			j;

	file_arr = (char **) ft_memalloc(sizeof(char *) * (flen + 1));
	if (!file_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < alen)
	{
		if ((*arr)[i])
			if (sfal_helper((*arr)[i], file_arr, &j, flg))
				ft_memdel((void **)&((*arr)[i]));
		i++;
	}
	return (file_arr);
}

static void	loop_helper(t_ls *flags, char *str, ssize_t *d_c, size_t *f_c)
{
	struct stat		stat_data;
	unsigned int	type;

	if (flags->list)
	{
		lstat(str, &stat_data);
		type = check_file_type(stat_data.st_mode);
		if (type == LNK)
		{
			(*f_c)++;
			return ;
		}
	}
	stat(str, &stat_data);
	type = check_file_type(stat_data.st_mode);
	if (type == DRC)
		(*d_c)++;
	else
		(*f_c)++;
}

static ssize_t	va_loop(char ***arr, t_ls *flags, ssize_t *d_c, size_t *f_c)
{
	struct stat		stat_data;
	ssize_t			len;

	len = 0;
	while ((*arr)[len])
	{
		if (stat((*arr)[len], &stat_data))
		{
			ft_printf("ft_ls: %s: No such file or directory\n", (*arr)[len]);
			ft_memdel((void **)&((*arr)[len]));
		}
		else
			loop_helper(flags, (*arr)[len], d_c, f_c);
		(len)++;
	}
	return (len);
}

void	validate_arr(char ***arr, t_ls *flags, unsigned int *files_printed)
{
	ssize_t			len;
	ssize_t			dir_count;
	size_t			fil_count;
	char			**files_and_links;

	fil_count = 0;
	dir_count = 0;
	len = va_loop(arr, flags, &dir_count, &fil_count);
	if (fil_count)
	{
		files_and_links = set_files_links(arr, fil_count, len, flags);
		file_display_control(files_and_links, flags);
		ft_freearray((void ***)&files_and_links, fil_count);
		if (dir_count)
			ft_putchar('\n');
		else
			ft_freearray((void ***)arr, fil_count);
	}
	if (dir_count && len > dir_count)
	{
		*files_printed = TRUE;
		trim_valid_arr(arr, len, dir_count);
	}
}
