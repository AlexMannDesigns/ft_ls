/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:36:03 by amann             #+#    #+#             */
/*   Updated: 2022/03/23 18:51:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	arr_swap(char ***arr, int *i)
{
	char	*temp;

	temp = (*arr)[(*i)];
	(*arr)[(*i)] = (*arr)[(*i) + 1];
	(*arr)[(*i) + 1] = temp;
	(*i) = 0;
}

void	sort_arr(char ***arr, t_ls *flags)
{
	int		i;

	i = 0;
	while ((*arr)[i + 1])
	{
	//	ft_putendl((*arr)[i]);
	//	ft_putendl((*arr)[i + 1]);
	//	ft_putendl("-----");
		if (!flags->reverse)
		{
			if (ft_strcmp((*arr)[i], (*arr)[i + 1]) > 0)
				arr_swap(arr, &i);
			else
				i++;
		}
		else
		{
			if (ft_strcmp((*arr)[i], (*arr)[i + 1]) < 0)	
				arr_swap(arr, &i);
			else                                        	
				i++;                                    
		}
	}
}
