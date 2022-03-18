/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:29:45 by amann             #+#    #+#             */
/*   Updated: 2022/03/18 17:14:21 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

//maybe add a version of this that takes a void** as arg to libft...
static size_t	check_arr_len(void **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
//	ft_printf("%zu\n", len);
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
	//ft_printf("%zu\n", i);
}

char	**directory_control(char **argv, t_ls *flags)
{
	char	**file_arr;
	size_t	arr_len;

	arr_len = check_arr_len((void **)argv);
	file_arr = (char **) ft_memalloc(sizeof(char *) * (arr_len + 1));
	if (!file_arr)
		return (NULL);
	copy_arr(&file_arr, argv);
	if (flags->reverse)
		return (argv);
	sort_arr(&file_arr);
//	ft_putendl("here");
	validate_arr(&file_arr);
	arr_len = check_arr_len((void **)file_arr);
	//size_t i = 0;
	//while (file_arr[i])
		//ft_printf("%s\n", file_arr[i++]);
	
	//ft_printf("len = %zu l_flag = %u\n", arr_len, flags->list);
	return (file_arr);
}