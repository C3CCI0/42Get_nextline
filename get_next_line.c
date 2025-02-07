/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbellin <frbellin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:29 by frbellin          #+#    #+#             */
/*   Updated: 2025/01/28 10:26:29 by frbellin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	i = 0;
	while ((bytes_read = read(fd, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	if (bytes_read <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	buffer[i] = '\0';
	return (line);
}

int	main()
{
	int		fd;
	char	*line;

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