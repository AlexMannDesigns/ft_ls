/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:39 by amann             #+#    #+#             */
/*   Updated: 2022/03/20 16:21:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	print_permissions(mode_t mode)
{
	unsigned int	type;

	type = check_file_type(mode);
	//ft_printf("%u\n", type);
	if (type == DRC)
		ft_putchar('d');
	else if (type == LNK)
		ft_putchar('l');
	else if (type == BLK)
		ft_putchar('b');
	else if (type == CHR)
		ft_putchar('c');
	else if (type == FFO)
		ft_putchar('f');
	else if (type == RGF)
		ft_putchar('-');
	ft_putchar(' ');
}

void	print_list(char **arr)
{
	struct stat	stat_data;
	size_t		i;

	i = 0;
	while (arr[i])
	{
		lstat(arr[i], &stat_data);
		print_permissions(stat_data.st_mode);
		ft_printf("%s\n", arr[i]);
		i++;
	}
}
