/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: frbellin <frbellin@student.42roma.it>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/28 10:26:29 by frbellin          #+#    #+#             */
/*   Updated: 2025/01/28 10:26:29 by frbellin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*find_slash_n(char *buffer, char *line, int fd)
{
	static int	i;

	i = 0;
	// int bytes_read;
	if (i == 0)
		read(fd, buffer, BUFFER_SIZE);
	while (i < BUFFER_SIZE + 1)
	{
		if (buffer[i] == '\n')
		{
			line[i] = '\n';
			break ;
		}
		//printf("%c\n", buffer[i]);
		line[i] = buffer[i];
		i++;
	}
	/* if (bytes_read <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	} */
	buffer[i] = '\0';
	return (line);
}
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static char	*line;

	// static int	bytes_read;
	// static int	i;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		printf("nope");
		return (NULL);
	}
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	find_slash_n(buffer, line, fd);
	return (line);
}

int	main(void)
{
	int fd;
	char *line;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}