/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:29:45 by amann             #+#    #+#             */
/*   Updated: 2022/04/01 17:59:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

size_t	check_arr_len(void **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

static void	copy_arr(char ***dest, char **src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		(*dest)[i] = ft_strdup(src[i]);
		i++;
	}
}

char	**directory_control(char **argv, t_ls *flags, unsigned int *printed)
{
	char	**file_arr;
	size_t	arr_len;

	arr_len = check_arr_len((void **)argv);
	file_arr = (char **) ft_memalloc(sizeof(char *) * (arr_len + 1));
	if (!file_arr)
		return (NULL);
	copy_arr(&file_arr, argv);
	sort_arr(&file_arr, flags, TRUE);
	validate_arr(&file_arr, flags, printed);
	if (file_arr)
		sort_arr(&file_arr, flags, FALSE);
	return (file_arr);
}
