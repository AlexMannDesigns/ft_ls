/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:25:12 by amann             #+#    #+#             */
/*   Updated: 2022/03/15 19:13:22 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

int	main(int ac, char **av)
{
//	time_t	seconds;
//
//	time(&seconds);
//	printf("the time since midnight 1/1/1970 in days = %ld\n", seconds/3600/24);
//	printf("the time is now: %s\n", ctime(&seconds));
//	
//	printf("the message for errno 5 is: %s\n", strerror(5));
//	printf("the message for errno 17 is: %s\n", strerror(17));
//	perror("hello world");
	DIR				*directory;
	struct dirent	*next_filename;	
	char			*name;

	printf("hello world\n");
	if (ac != 2)
	{
		printf("please provide the name of one directory\n");
		return (1);
	}
	directory = opendir(av[1]);
   	if (!directory)
	{
		printf("not a valid directory\n");
		return (1);
	}
	next_filename = readdir(directory);
	while (next_filename)
	{
		name = next_filename->d_name;
		if (name[0] != '.')
			printf("%s\n", name);
		next_filename = readdir(directory);
	}
	closedir(directory);
	return (0);
}

