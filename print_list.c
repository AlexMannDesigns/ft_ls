/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:39 by amann             #+#    #+#             */
/*   Updated: 2022/03/22 16:55:38 by amann            ###   ########.fr       */
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

//function will also have to print individual files
//separate functions called in loop to a control function which can be called
//with the file path parsed

void	handle_links(int links)
{
	
}

static char	*username(uid_t st_uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(st_uid);
	if (pwd)
		return (pwd->pw_name);
	return ("Unkown");
}

static void	update_max_width(t_fields *field_width, size_t *width_arr, size_t i, size_t len)
{


}

static void	initialise_field_widths(t_fields *field_width, char **arr, char *path, size_t arr_len)
{
	size_t		i;
	size_t		j;
	size_t		*width_arr;
	char		*str;
	char		*file_path;
	struct stat	stat_data;
	//malloc new size_t array
	//create strings for each value and strlen them into the array
	//find max value in array and update struct
	width_arr = (size_t *) ft_memalloc(sizeof(size_t) * arr_len);
	if (!width_arr)
		return ; //failsafe needed to set all widths to a value...
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < arr_len)
		{
			file_path = create_file_path(arr[j], path, TRUE);
			lstat(file_path, &stat_data);
			if (i == 0)
				str = ft_itoa(stats.st_nlink);
			if (i == 1) 
				str = ft_strdup(username(stats.st_uid));	
			if (i == 2)
				str = ft_itoa(stats.st_gid);
			if (i == 3)
				str = ft_itoa_base(stats.st_size);
			if (str)
			{
				width_arr[j] = ft_strlen(str);
				free(str);
			}
			else
				return ;
			j++;
		}
		update_max_width(field_width, width_arr, i, arr_len);		
		i++;
	}
}

void	print_list(char **arr, char *path, unsigned int is_dir, size_t arr_len)
{
	struct stat	stat_data;
	size_t		i;
	char		*file_path;
	t_fields	field_width;

	if (is_dir)
		ft_printf("total \n"); //add memory blocks here
	initialise_field_widths(&field_width, arr, path, arr_len);
	i = 0;
	while (arr[i])
	{
		file_path = create_file_path(arr[i], path, TRUE);
		lstat(file_path, &stat_data);
		handle_permissions_and_type(stat_data.st_mode);
		handle_links(stat_data.st_nlink);
		ft_printf("%s\n", arr[i]);
		//ft_printf("\t%s\n", file_path);
		ft_memdel((void **)&file_path);
		i++;
	}
}
