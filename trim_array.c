/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:35:37 by amann             #+#    #+#             */
/*   Updated: 2022/03/31 13:37:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static char	**trim_arr_loop(char **arr, ssize_t len, ssize_t o_len, ssize_t c)
{
	char	**res;

	res = (char **) ft_memalloc(sizeof(char *) * (c + 1));
	if (!res)
	{
		ft_freearray((void ***)&arr, len);
		return (NULL);
	}
	while (len >= 0)
	{
		if (arr[len])
		{
			c--;
			res[c] = ft_strdup(arr[len]);
			if (!res[c])
			{
				ft_freearray((void ***)&arr, o_len);
				return (NULL);
			}
		}
		len--;
	}
	return (res);
}

void	trim_valid_arr(char ***arr, ssize_t len, ssize_t count)
{
	char	**new_arr;
	ssize_t	orig_len;

	orig_len = len;
	new_arr = trim_arr_loop(*arr, len, orig_len, count);
	if (*arr)
		ft_freearray((void ***)arr, orig_len);
	(*arr) = new_arr;
}
