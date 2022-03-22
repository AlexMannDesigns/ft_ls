/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:39 by amann             #+#    #+#             */
/*   Updated: 2022/03/22 12:56:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*create_file_path(char *name, char *path, unsigned int list)
{
	char	*res;
	char	*temp;

	if (list && ft_strcmp(path, "./") == 0)
		return (ft_strdup(name));
	if (list || ft_strcmp(path, "./"))
		temp = ft_strjoin(path, "/");
	else
		temp = ft_strdup(path);
	res = ft_strjoin(temp, name);
	free(temp);
	return (res);
}	

//function will also have to print individual files
//separate functions called in loop to a control function which can be called
//with the file path parsed
void	print_list(char **arr, char *path)
{
	struct stat	stat_data;
	size_t		i;
	char		*file_path;

	ft_printf("total \n"); //add memory blocks here
	i = 0;
	while (arr[i])
	{
		file_path = create_file_path(arr[i], path, TRUE);
		lstat(file_path, &stat_data);
		handle_permissions_and_type(stat_data.st_mode);
		ft_printf("%s\n", arr[i]);
		//ft_printf("\t%s\n", file_path);
		ft_memdel((void **)&file_path);
		i++;
	}
}
