/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:47:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/14 18:37:13 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(sizeof(char) * (size));
	if (!ptr)
		return (NULL);
	while (i < (size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*read_buffer(int fd, char *buffer, ssize_t *flagB)
{
	int n;

	n = ft_strlen(buffer);
	flagB = 0; // flags: ERR (-1) | EOF (0) | bytes (+)
	flagB = (ssize_t *)read(fd, buffer, BUFFER_SIZE);
	if (flagB <= 0)
		return(NULL);
	buffer[n] = '\0';
	return (buffer);
}

char	*build_cache(int fd, char *cache, ssize_t *flagB) //calloc buffer & free buffer
{
	char	*buffer;

	//buffer = ft_calloc(BUFFER_SIZE + 1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buffer = read_buffer(fd, buffer, flagB);
	cache = ft_strdup(buffer);
	free(buffer);
	return (cache);
}

char	*get_next_line(int fd)
{
	char *line;
	ssize_t	flagB;

	line = NULL;
	flagB = 0;
	line = build_cache(fd, line, &flagB);
	if (BUFFER_SIZE < 1 || fd < 0 || fd > MAX_FD || flagB <= 0)
		return (NULL);
	return(line);
}


int	main(void)//TODO: Implement argc, argv
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("t0.txt", O_RDONLY);
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(str != NULL);
	return (0);
}

