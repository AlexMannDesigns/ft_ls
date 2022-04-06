/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_and_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:05:57 by amann             #+#    #+#             */
/*   Updated: 2022/03/28 13:08:51 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*username(uid_t st_uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(st_uid);
	if (pwd)
		return (pwd->pw_name);
	return ("Unkown");
}

char	*group_id(gid_t grp_id)
{
	struct group	*grp;

	grp = getgrgid(grp_id);
	if (grp)
		return (grp->gr_name);
	return ("Unknown");
}
