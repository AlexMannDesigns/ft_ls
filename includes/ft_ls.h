/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:22:07 by amann             #+#    #+#             */
/*   Updated: 2022/03/23 12:41:25 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/***** HEADER FILES *****/

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <grp.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <time.h>
# include <stdio.h>

/***** MACROS *****/

# define TRUE 1
# define FALSE 0

# define RGF 1
# define DRC 2
# define LNK 3
# define BLK 4
# define CHR 5
# define FFO 6

# define FLAGS "lRart"
# define USAGE	"usage: ./ft_ls -[alrRt] [file ...]"

/***** STRUCT PROTOTYPING *****/

typedef struct s_ls
{
	unsigned int	list;
	unsigned int	recursive;
	unsigned int	reverse;
	unsigned int	all;
	unsigned int	time;
}					t_ls;

typedef struct s_fields
{
	size_t	links;
	size_t	user;
	size_t	group;
	size_t	size;
	char	**links_arr;
	char	**user_arr;
	char	**group_arr;
	char	**size_arr;
}			t_fields;

/***** FUNCTION PROTOTYPING *****/

/* ft_ls.c */

/* check_flags.c */
int		option_control(char ***argv, t_ls **flags);
void	initialise_flags(t_ls **flags);

/* display_control.c */
void	display_control(char *dir_name, t_ls *flag);

/* print_basic.c */
void	print_basic(char **arr);

/* print_list.c */
void	print_list(char **arr, char *path, unsigned int is_dir, size_t arr_len);
char	*create_file_path(char *name, char *path, unsigned int list);

/* permissions_control.c */
void	handle_permissions_and_type(mode_t mode);

/* initialise_fields.c */
void	init_fields(t_fields *f_width, char **arr, char *path, size_t len);

/* sort_array.c */
void	sort_arr(char ***arr);

/* directory_control.c */
char	**directory_control(char **argv, t_ls *flags, unsigned int *files_printed);

size_t	check_arr_len(void **arr);

/* validate_array.c */
void	validate_arr(char ***arr, t_ls *flags, unsigned int *files_printed);

/* check_file_type.c */
unsigned int	check_file_type(mode_t st_mode);
#endif
