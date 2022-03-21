/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:50:21 by amann             #+#    #+#             */
/*   Updated: 2022/03/21 11:50:37 by amann            ###   ########.fr       */
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

void	handle_permissions_and_type(mode_t mode)
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
