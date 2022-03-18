/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:22:07 by amann             #+#    #+#             */
/*   Updated: 2022/03/18 17:27:25 by amann            ###   ########.fr       */
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

/***** FUNCTION PROTOTYPING *****/

/* ft_ls.c */

/* check_flags.c */
int		option_control(char ***argv, t_ls **flags);
void	initialise_flags(t_ls **flags);

/* basic_display.c */
void	basic_display(char *dir_name, int a_flag);

/* print_basic.c */
void	print_basic(char **arr);

/* sort_array.c */
void	sort_arr(char ***arr);

/* directory_control.c */
char	**directory_control(char **argv, t_ls *flags);

size_t	check_arr_len(void **arr);

/* validate_array.c */
void	validate_arr(char ***arr);
#endif
