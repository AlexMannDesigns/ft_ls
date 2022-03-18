/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:36:03 by amann             #+#    #+#             */
/*   Updated: 2022/03/18 14:16:22 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	sort_arr(char ***arr)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*arr)[i + 1])
	{
		//ft_putendl((*arr)[i]);
		//ft_putendl((*arr)[i + 1]);
		//ft_putendl("-----");
		if (ft_strcmp((*arr)[i], (*arr)[i + 1]) > 0)
		{
			temp = (*arr)[i];
			(*arr)[i] = (*arr)[i + 1];
			(*arr)[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}