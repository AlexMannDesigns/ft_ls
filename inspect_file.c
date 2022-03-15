/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:59:37 by amann             #+#    #+#             */
/*   Updated: 2022/03/15 19:29:35 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <time.h>

static char	*file_type(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		return ("File");
	if (S_ISDIR(st_mode))
		return ("Directory");
	if (S_ISLNK(st_mode))
		return ("Symbolic Link");
	return ("Unknown");
}

static char *username(uid_t st_uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(st_uid);
	if (pwd)
		return (pwd->pw_name);
	return ("Unknown User");
}

static void	access_types(mode_t mode)
{
	if (mode & S_IRUSR)
		printf("Read ");
	if (mode & S_IWUSR)
		printf("Write ");
	if (mode & S_IXUSR)
		printf("Execute");
	printf("\n");
}

int main(int ac, char **av)
{
	struct stat		stats;
	off_t			size;
	char			*type;

	if (ac != 2)
	{
		printf("please enter a one filename\n");
		return (1);
	}
	if (stat(av[1], &stats) != 0)
	{
		printf("invalid filename\n");
		return (1);
	}
	printf("\nfilename:		%s\n", av[1]);
	printf("filetype:		%s\n", file_type(stats.st_mode));
	printf("file access:		");
	access_types(stats.st_mode);
	printf("file creator:		%s\n", username(stats.st_uid));
	printf("group id: 		%d\n", stats.st_gid);
	printf("last edited:		%s", ctime(&stats.st_mtimespec.tv_sec));
	printf("hard links:		%d\n", stats.st_nlink);
	printf("blocks: 		%lld\n", stats.st_blocks);
	printf("file size:		%lld\n", stats.st_size);
	return (0);
}
