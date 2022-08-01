/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:50:19 by amann             #+#    #+#             */
/*   Updated: 2022/07/29 11:15:50 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

ssize_t	ft_putstr(char const *str)
{
	ssize_t	res;

	if (!str)
		return (0);
	res = write(1, str, ft_strlen(str));
	return (res);
}
