/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:39 by amann             #+#    #+#             */
/*   Updated: 2022/04/14 13:34:51 by amann            ###   ########.fr       */
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

static void	lnk_usr_grp_sz(t_fields f_width, size_t i, t_file_info *current)
{
	int	maj;
	int	min;

	ft_printf("%*s ", f_width.links, (f_width.links_arr)[i]);
	ft_printf("%-*s", f_width.user, (f_width.user_arr)[i]);
	ft_printf("%-*s", f_width.group, (f_width.group_arr)[i]);
	if (current->type == BLK || current->type == CHR)
	{
		maj = major(current->stats.st_rdev);
		min = minor(current->stats.st_rdev);
		if (min > 500)
			ft_printf("%4d, %0#10x", maj, min);
		else
			ft_printf("%4d, %3d", maj, min);
	}
	else
		ft_printf("%*s", f_width.size, (f_width.size_arr)[i]);
}

static void	handle_time(t_file_info *current)
{
	time_t			time_now;
	time_t			time_modded;
	char			*mod_time;
	char			*res;
	char			year[5];

	time(&time_now);
	time_modded = current->modified;
	mod_time = ctime(&current->modified);
	res = ft_strsub(mod_time, 4, 12);
	if (time_now - time_modded < SIX_MONTHS_IN_SECONDS
		&& time_now >= time_modded)
	{
		ft_printf("%13s", res);
		free(res);
		return ;
	}
	ft_strncpy(year, mod_time + 20, 4);
	year[4] = '\0';
	ft_printf("%8.7s %s", res, year);
	free(res);
}

void	free_field_width_struct(t_fields field_width, size_t len)
{
	ft_freearray((void ***)&field_width.links_arr, len - 1);
	ft_freearray((void ***)&field_width.user_arr, len - 1);
	ft_freearray((void ***)&field_width.group_arr, len - 1);
	ft_freearray((void ***)&field_width.size_arr, len - 1);
}

void	print_list(t_list *lst, size_t lst_len, unsigned int prnt_d, t_ls *flg)
{
	t_file_info	*current;
	t_fields	field_width;
	t_list		*head;
	size_t		i;

	init_fields(&field_width, lst, lst_len, flg);
	if (prnt_d == TRUE && lst)
		ft_printf("total: %lld\n", field_width.blocks);
	head = lst;
	i = 0;
	while (lst)
	{
		current = (t_file_info *)lst->content;
		handle_permissions_and_type(current);
		lnk_usr_grp_sz(field_width, i, current);
		handle_time(current);
		ft_printf(" %s", current->name);
		if (current->type == LNK)
			ft_printf(" -> %s", current->links_to);
		ft_putchar('\n');
		lst = lst->next;
		i++;
	}
	lst = head;
	free_field_width_struct(field_width, i);
}
