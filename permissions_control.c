/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:50:21 by amann             #+#    #+#             */
/*   Updated: 2022/04/05 18:42:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	add_file_type(char *perm_str, unsigned int type)
{
	if (type == DRC)
		perm_str[0] = 'd';
	else if (type == LNK)
		perm_str[0] = 'l';
	else if (type == BLK)
		perm_str[0] = 'b';
	else if (type == CHR)
		perm_str[0] = 'c';
	else if (type == FFO)
		perm_str[0] = 'p';
	else if (type == RGF)
		perm_str[0] = '-';
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
	if ((mode & S_IXUSR) && (mode & S_ISUID))
		perm_str[3] = 's';
	else if (!(mode & S_IXUSR) && (mode & S_ISUID))
		perm_str[3] = 'S';
	else if (mode & S_IXUSR)
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
	if ((mode & S_IXGRP) && (mode & S_ISGID))
		perm_str[6] = 's';
	else if (!(mode & S_IXGRP) && (mode & S_ISGID))
		perm_str[6] = 'S';
	else if (mode & S_IXGRP)
		perm_str[6] = 'x';
	else
		perm_str[6] = '-';
}

static void	add_other_permissions(char *perm_str, t_file_info *file)
{
	mode_t	mode;

	mode = file->stats.st_mode;
	if (mode & S_IROTH)
		perm_str[7] = 'r';
	else
		perm_str[7] = '-';
	if (mode & S_IWOTH)
		perm_str[8] = 'w';
	else
		perm_str[8] = '-';
	if ((mode & S_IXOTH) && !(mode & S_ISVTX))
		perm_str[9] = 'x';
	else if ((mode & S_IXOTH) && (mode & S_ISVTX))
		perm_str[9] = 't';
	else if (!(mode & S_IXOTH) && (mode & S_ISVTX))
		perm_str[9] = 'T';
	else
		perm_str[9] = '-';
	extended_attr_and_acl(perm_str, file);
}

void	handle_permissions_and_type(t_file_info *file)
{
	char	*perm_str;

	perm_str = ft_strnew(11);
	if (!perm_str)
		return ;
	add_file_type(perm_str, file->type);
	add_user_permissions(perm_str, file->stats.st_mode);
	add_group_permissions(perm_str, file->stats.st_mode);
	add_other_permissions(perm_str, file);
	ft_printf("%-11s", perm_str);
	free(perm_str);
}
