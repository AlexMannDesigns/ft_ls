/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:39 by amann             #+#    #+#             */
/*   Updated: 2022/03/21 11:43:18 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void add_file_type(char *perm_str, mode_t mode)
{
	unsigned int	type;

	type = check_file_type(mode);
	if (type == DRC)
		perm_str[0] = 'd';
	else if (type == LNK)
		perm_str[0] = 'l';
	else if (type == BLK)
		perm_str[0] = 'b';
	else if (type == CHR)
		perm_str[0] = 'c';
	else if (type == FFO)
		perm_str[0] = 'f'; 
	else if (type == RGF)
		perm_str[0] ='-';
}

static void	add_user_permissions(char *perm_str, mode_t mode)
{
	if (mode & S_IRUSR)
		perm_str[1] = 'r';
	else
		perm_str[1] = '-';
	if (mode & S_IWUSR)
		perm_str[2] = 'w';
	else
		perm_str[2] = '-';
	if (mode & S_IXUSR)
		perm_str[3] = 'x';
	else
		perm_str[3] = '-';
}

static void	add_group_permissions(char *perm_str, mode_t mode)
{
	if (mode & S_IRGRP)
		perm_str[4] = 'r';
	else
		perm_str[4] = '-';
	if (mode & S_IWGRP)
		perm_str[5] = 'w';
	else
		perm_str[5] = '-';
	if (mode & S_IXGRP)
		perm_str[6] = 'x';
	else
		perm_str[6] = '-';
}

static void	add_other_permissions(char *perm_str, mode_t mode)
{
	if (mode & S_IROTH)
		perm_str[7] = 'r';
	else
		perm_str[7] = '-';
	if (mode & S_IWOTH)
		perm_str[8] = 'w';
	else
		perm_str[8] = '-';
	if (mode & S_IXOTH)
		perm_str[9] = 'x';
	else
		perm_str[9] = '-';
}

static void	handle_permissions_and_type(mode_t mode)
{
	char	*perm_str;

	perm_str = ft_strnew(11);
	if (!perm_str)
		return ;
	add_file_type(perm_str, mode);
	add_user_permissions(perm_str, mode);
	add_group_permissions(perm_str, mode);
	add_other_permissions(perm_str, mode);		
	ft_printf("%-11s", perm_str);
	free(perm_str);
}

static char	*create_file_path(char *name, char *path)
{
	char	*res;
	char	*temp;

	if (!ft_strcmp(path, "./"))
		return (ft_strdup(name));
	temp = ft_strjoin(path, "/");
	res = ft_strjoin(temp, name);
	free(temp);
	return (res);
}	

void	print_list(char **arr, char *path)
{
	struct stat	stat_data;
	size_t		i;
	char		*file_path;

	ft_printf("total \n"); //add memory blocks here
	i = 0;
	while (arr[i])
	{
		file_path = create_file_path(arr[i], path);
		lstat(file_path, &stat_data);
		handle_permissions_and_type(stat_data.st_mode);
		ft_printf("%s\n", arr[i]);
		//ft_printf("\t%s\n", file_path);
		ft_memdel((void **)&file_path);
		i++;
	}
}
