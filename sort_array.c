/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:36:03 by amann             #+#    #+#             */
/*   Updated: 2022/04/06 15:13:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int	arr_swap(char ***arr, int *i)
{
	char	*temp;

	temp = (*arr)[(*i)];
	(*arr)[(*i)] = (*arr)[(*i) + 1];
	(*arr)[(*i) + 1] = temp;
	(*i) = 0;
	return (1);
}

static int	compare_modified(char *obj1, char *obj2, t_ls *flags)
{
	struct stat	stat_data1;
	struct stat	stat_data2;

	lstat(obj1, &stat_data1);
	lstat(obj2, &stat_data2);
	if (stat_data1.st_mtime < stat_data2.st_mtime)
		return (1);
	else if (stat_data1.st_mtime == stat_data2.st_mtime)
	{
		if (flags->reverse && ft_strcmp(obj1, obj2) > 0)
			return (1);
		else
			return (0);
	}	
	else
		return (0);
}

static int	sort_dispatcher(char ***arr, t_ls *flags, int *i, unsigned int sani)
{
	if (((!flags->reverse && !flags->time) || sani)
		&& ft_strcmp((*arr)[(*i)], (*arr)[(*i) + 1]) > 0)
		return (arr_swap(arr, i));
	else if (flags->reverse && !flags->time && !sani
		&& ft_strcmp((*arr)[(*i)], (*arr)[(*i) + 1]) < 0)
		return (arr_swap(arr, i));
	else if (!flags->reverse && flags->time && !sani
		&& compare_modified((*arr)[(*i)], (*arr)[(*i) + 1], flags))
		return (arr_swap(arr, i));
	else if (flags->reverse && flags->time && !sani
		&& !compare_modified((*arr)[(*i)], (*arr)[(*i) + 1], flags))
		return (arr_swap(arr, i));
	else
		return (0);
}

void	sort_arr(char ***arr, t_ls *flags, unsigned int sanitising)
{
	int		i;

	i = 0;
	while ((*arr)[i + 1])
	{
		if (!sort_dispatcher(arr, flags, &i, sanitising))
			i++;
	}
}
