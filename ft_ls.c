/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:39:01 by amann             #+#    #+#             */
/*   Updated: 2022/03/16 19:22:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	basic_display(int a_flag)
{
	DIR				*directory;
	struct dirent	*next_filename;
	char			*name;

	directory = opendir("./");
	if (!directory)
	{
		ft_printf("there was an error\n");
		return ;
	}
	next_filename = readdir(directory);
	while (next_filename)
	{
		name = next_filename->d_name;
		if (!a_flag)
		{
			if (name[0] != '.')
				ft_printf("%s\t", name);
		}
		else
			ft_printf("%s\t", name);
		next_filename = readdir(directory);
	}
	ft_printf("\n");
	closedir(directory);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		basic_display(FALSE);
	else
		return (1);
	argv[0] = "hello";
	return (0);
}
