/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_fields.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:27:08 by amann             #+#    #+#             */
/*   Updated: 2022/03/23 14:24:58 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static char	*username(uid_t st_uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(st_uid);
	if (pwd)
		return (pwd->pw_name);
	return ("Unkown");
}

static void	max_width(t_fields *f_width, size_t *w_arr, size_t col, size_t len)
{
	size_t	i;
	size_t	max;

	max = 0;
	i = 0;
	while (i < len)
	{
		if (w_arr[i] > max)
			max = w_arr[i];
		i++;
	}
	max++;
	if (col == 0)
		f_width->links = max;
	if (col == 1)
		f_width->user = max;
	if (col == 2)             	
		f_width->group = max + 1;
	if (col == 3)
		f_width->size = max + 1;
}

void	init_fields(t_fields *f_width, char **arr, char *path, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		*w_arr;
	char		*file_path;
	struct stat	stat_data;
	//malloc new size_t array
	//create strings for each value and strlen them into the array
	//find max value in array and update struct
	w_arr = (size_t *) ft_memalloc(sizeof(size_t) * len);
	f_width->links_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->user_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->group_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->size_arr = (char **) ft_memalloc(sizeof(char *) * len);
	f_width->blocks = 0;
	//ft_printf("%zu\n", len);
	if (!w_arr)
		return ; //failsafe needed to set all widths to a value...
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < len)
		{
			file_path = create_file_path(arr[j], path, TRUE);
			lstat(file_path, &stat_data);
			if (i == 0)
			{
				(f_width->links_arr)[j] = ft_itoa(stat_data.st_nlink);
				w_arr[j] = ft_strlen((f_width->links_arr)[j]);
				f_width->blocks += stat_data.st_blocks;
			}
			else if (i == 1)
			{	
				(f_width->user_arr)[j] = ft_strdup(username(stat_data.st_uid));	
				w_arr[j] = ft_strlen((f_width->user_arr)[j]);
			}
			else if (i == 2)
			{
				(f_width->group_arr)[j] = ft_itoa(stat_data.st_gid);
				w_arr[j] = ft_strlen((f_width->group_arr)[j]);
			}
			else if (i == 3)
			{
				(f_width->size_arr)[j] = ft_itoa_base(stat_data.st_size, 10);
				w_arr[j] = ft_strlen((f_width->size_arr)[j]);
			}
			free(file_path);
			j++;
		}
		max_width(f_width, w_arr, i, len);		
		i++;
	}
	free(w_arr);
}
