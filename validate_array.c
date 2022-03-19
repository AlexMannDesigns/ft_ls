/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:41:35 by amann             #+#    #+#             */
/*   Updated: 2022/03/19 17:44:48 by amann            ###   ########.fr       */
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

void	validate_arr(char ***arr)
{
	ssize_t	len;
	ssize_t	count;
	DIR		*current;

	len = 0;
	count = 0;
	while ((*arr)[len])
	{
//		ft_printf("%zu %s\n", len, (*arr)[len]);
		current = opendir((*arr)[len]);
		if (!current)
		{
			//check file type here - could be a valid file or sym link
			//in fact, maybe just checking the file type will be better than using opendir...
			ft_printf("ft_ls: %s: No such file or directory\n", (*arr)[len]);
			ft_memdel((void **)&((*arr)[len]));	
		}
		else
		{
			closedir(current);
			count++;
		}
		len++;
	}
	if (len > count)
		trim_valid_arr(arr, len, count);
}

