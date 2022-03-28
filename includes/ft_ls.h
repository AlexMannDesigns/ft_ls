/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:22:07 by amann             #+#    #+#             */
/*   Updated: 2022/03/28 13:20:56 by amann            ###   ########.fr       */
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

# define LS_BUF_SIZE 100
# define SIX_MONTHS_IN_SECONDS 15778463

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
	size_t			links;
	size_t			user;
	size_t			group;
	size_t			size;
	long long int	blocks;
	char			**links_arr;
	char			**user_arr;
	char			**group_arr;
	char			**size_arr;
}					t_fields;

typedef struct s_file_info
{
	struct stat		stats;
	unsigned int	type;
	char			*name;
	char			*dir_name;
	char			*path;
	uid_t			user;
	gid_t			group;
	time_t			modified;
	time_t			created;
	int				links;
	long long int	blocks;
	long long int	size;
	char			*links_to;
}					t_file_info;

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
void	print_list(t_list *list, size_t list_len, unsigned int print_dir);
char	*create_file_path(char *name, char *path, unsigned int list);

/* permissions_control.c */
void	handle_permissions_and_type(t_file_info *file);

/* initialise_fields.c */
void	init_fields(t_fields *f_width, t_list *list, size_t len);

/* init_fields_loop.c */
void	init_fields_loop(t_list *list, t_fields *f_width, size_t *w_arr, size_t i);

/* user_and_grooup.c */
char	*username(uid_t st_uid);
char	*group_id(gid_t grp_id);

/* sort_array.c */
void	sort_arr(char ***arr, t_ls *flags, unsigned int sanitising);

/* sort_node_list.c */
void	sort_node_list(t_list **list, t_ls *flags);

/* directory_control.c */
char	**directory_control(char **argv, t_ls *flags, unsigned int *files_printed);

size_t	check_arr_len(void **arr);

/* validate_array.c */
void	validate_arr(char ***arr, t_ls *flags, unsigned int *files_printed);

/* check_file_type.c */
unsigned int	check_file_type(mode_t st_mode);

/* list_constructor.c */
t_list	*list_constructor(char *dir, t_ls *flags, size_t *len);
void	list_const_helper(char *file_name, char *dir, t_list **file_list);

/* check_malloc.c */
int		check_struct_malloc(t_file_info **info);

/* file_display_control.c */
void	file_display_control(char **arr, t_ls *flags);

#endif
