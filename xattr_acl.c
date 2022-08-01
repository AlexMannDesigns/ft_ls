/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:22:13 by amann             #+#    #+#             */
/*   Updated: 2022/07/29 13:12:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"


void	extended_attr_and_acl(char *perm_str, t_file_info *file)
{
	#ifdef __APPLE__
	acl_t	acl;

	acl = acl_get_file(file->path, ACL_TYPE_EXTENDED);
	if (acl)
	{
		perm_str[10] = '+';
		acl_free(acl);
	}
	#endif
	if (file->attr > 0)
		perm_str[10] = '@';
}

