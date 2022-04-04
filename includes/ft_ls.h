/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:22:07 by amann             #+#    #+#             */
/*   Updated: 2022/04/04 18:28:55 by amann            ###   ########.fr       */
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
# include <sys/ioctl.h>
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

# define FLAGS "Ralmnrt1"
# define USAGE	"usage: ./ft_ls [-Ralmnrt1] [file ...]"

/***** STRUCT PROTOTYPING *****/

typedef struct s_ls
{
	unsigned int	list;
	unsigned int	recursive;
	unsigned int	reverse;
	unsigned int	all;
	unsigned int	time;
	unsigned int	one;
	unsigned int	comma;
	unsigned int	group_no;
	unsigned int	args_passed;
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

typedef struct s_columns
{
	size_t	col_width;
	size_t	col_height;
	size_t	col_number;
}			t_columns;

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
	ssize_t			attr;
}					t_file_info;

/***** FUNCTION PROTOTYPING *****/

/* check_flags.c */
int			option_control(char ***argv, t_ls **flags);
void		initialise_flags(t_ls **flags);

/* display_control.c */
void		display_control(char *dir_name, t_ls *flag);
void		display_dispatcher(t_list *file_list, t_ls *flags, size_t len);

/* print_basic.c */
void		print_basic(t_list *lst, size_t len);

/* column_data.c */
size_t		set_col_width(t_list *lst);
size_t		set_col_number(size_t col_width);
size_t		set_col_height(size_t col_number, size_t len);

/* print_list.c */
void		print_list(t_list *list, size_t list_len, unsigned int print_dir, t_ls *flags);
char		*create_file_path(char *name, char *path, unsigned int list);

/* print_other.c */
void		print_other(t_list *lst, char type);

/* permissions_control.c */
void		handle_permissions_and_type(t_file_info *file);

/* initialise_fields.c */
void		init_fields(t_fields *f_width, t_list *list, size_t len, t_ls *flags);

/* init_fields_loop.c */
void		init_fields_loop(t_list *list, t_fields *f_width, t_ls *flg, size_t *w_a);

/* user_and_grooup.c */
char		*username(uid_t st_uid);
char		*group_id(gid_t grp_id);

/* sort_array.c */
void		sort_arr(char ***arr, t_ls *flags, unsigned int sanitising);

/* sort_node_list.c */
void		sort_node_list(t_list **list, t_ls *flags);

/* sorting_flag_checks.c */
int			standard_lexico(t_file_info *c, t_file_info *n, t_ls *flags);
int			reverse_lexico(t_file_info *c, t_file_info *n, t_ls *flags);
int			standard_time(t_file_info *c, t_file_info *n, t_ls *flags);
int			reverse_time(t_file_info *c, t_file_info *n, t_ls *flags);

/* directory_control.c */
char		**directory_control(char **argv, t_ls *flags, \
			unsigned int *files_printed);

size_t		check_arr_len(void **arr);

/* validate_array.c */
void		validate_arr(char ***arr, t_ls *flags, unsigned int *files_printed);

/* trim_array.c */
void		trim_valid_arr(char ***arr, ssize_t len, ssize_t count);

/* check_file_type.c */
int			check_file_type(mode_t st_mode);

/* list_constructor.c */
t_list		*list_constructor(char *dir, t_ls *flags, size_t *len, \
			unsigned int *error);
void		list_const_helper(char *file_name, char *dir, t_list **file_list);

/* initialise_file_info.c */
t_file_info	*initialise_file_info(char *file_name, char *dir);

/* check_malloc.c */
int			check_struct_malloc(t_file_info **info);

/* file_display_control.c */
void		file_display_control(char **arr, t_ls *flags);

/* free_info_struct.c */
void		free_info_struct(void *info, size_t content_size);

#endif
