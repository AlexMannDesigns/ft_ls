/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:31:24 by amann             #+#    #+#             */
/*   Updated: 2022/07/29 11:15:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

ssize_t	ft_putstr_fd(char const *s, int fd)
{
	ssize_t	res;

	if (!s || !fd)
		return (0);
	res = write(fd, s, ft_strlen(s));
	return (res);
}
