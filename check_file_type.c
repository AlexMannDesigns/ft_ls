/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:19:47 by amann             #+#    #+#             */
/*   Updated: 2022/04/01 16:48:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_file_type(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		return (RGF);
	if (S_ISDIR(st_mode))
		return (DRC);
	if (S_ISLNK(st_mode))
		return (LNK);
	if (S_ISBLK(st_mode))
		return (BLK);
	if (S_ISCHR(st_mode))
		return (CHR);
	if (S_ISFIFO(st_mode))
		return (FFO);
	else
		return (0);
}
