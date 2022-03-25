/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:39 by amann             #+#    #+#             */
/*   Updated: 2022/03/25 16:49:35 by amann            ###   ########.fr       */
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

static void	handle_lnk_usr_grp_size(t_fields field_width, size_t i)
{
	ft_printf("%*s", field_width.links, (field_width.links_arr)[i]);
	ft_printf("%*s", field_width.user, (field_width.user_arr)[i]);
	ft_printf("%*s", field_width.group, (field_width.group_arr)[i]);
	ft_printf("%*s", field_width.size, (field_width.size_arr)[i]);
}

static void	handle_time(t_file_info *current)
{
	long long int	six_months;
	time_t			time_now;
	time_t			time_modded;
	char			*mod_time;
	char			*res;
	char			year[5];
	
	//check mod time is within last 6 months
	six_months = SIX_MONTHS_IN_SECONDS;
	time(&time_now);
	time_modded = current->modified;
	mod_time = ctime(&current->modified);
	res = ft_strsub(mod_time, 4, 12);
	if (time_now - time_modded < six_months)
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

void	print_list(t_list *list, size_t list_len)
{
	t_file_info	*current;
	t_fields	field_width;
	t_list		*head;
	size_t		i;

	init_fields(&field_width, list, list_len);
	ft_printf("total: %lld\n", field_width.blocks); 
	head = list;
	i = 0;
	while (list)
	{
		current = (t_file_info *)list->content;
		handle_permissions_and_type(current);
		handle_lnk_usr_grp_size(field_width, i);
		handle_time(current);
		ft_printf(" %s", current->name);	
    	if (current->type == LNK)
			ft_printf(" -> %s", current->links_to);
		ft_putchar('\n');	
		list = list->next;	
		i++;
	}
	list = head;
	//free up heap memory pointed to in field_width
}
