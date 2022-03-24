/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:59:37 by amann             #+#    #+#             */
/*   Updated: 2022/03/24 14:00:03 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

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
	if (S_ISDIR(mode))
		printf("d");
	else
		printf("-");
	if (mode & S_IRUSR)
		printf("r");
	else
		printf("-");
	if (mode & S_IWUSR)
		printf("w");
	else
		printf("-");
	if (mode & S_IXUSR)
		printf("x");
	else
		printf("-");
	printf("\n");
}

static char	*get_filename(ino_t serial_no)
{
	DIR				*current;
	struct dirent	*file;
	ino_t			file_serial;

	current = opendir("./");
	file = readdir(current);
	while (file)
	{
		file_serial = file->d_ino;
		if (file_serial == serial_no)
			return (file->d_name);
		file = readdir(current);
	}
	closedir(current);
	return ("unknown");
}

int main(int ac, char **av)
{
	struct stat		stats;
	off_t			size;
	char			*type;
	struct tm		dt;
	char year[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};


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
	dt = *(gmtime(&stats.st_ctime));
	printf("\nfilename:		%s\n", get_filename(stats.st_ino));
	printf("filetype:		%s\n", file_type(stats.st_mode));
	printf("file access:		");
	access_types(stats.st_mode);
	printf("file creator:		%s\n", username(stats.st_uid));
	printf("group id: 		%d\n", stats.st_gid);
	printf("time created:		%s %d %d:%d\n", year[dt.tm_mon], dt.tm_mday, dt.tm_hour, dt.tm_min);
	printf("last edited:		%s", ctime(&stats.st_mtime));
	printf("hard links:		%d\n", stats.st_nlink);
	printf("blocks: 		%lld\n", stats.st_blocks);
	printf("file size:		%lld\n", stats.st_size);

	char buf[100];
	listxattr("./", buf, 100, 0);
	printf("\n%s\n", buf);
	return (0);
}
