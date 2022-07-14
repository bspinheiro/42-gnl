/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:47:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/14 17:42:47 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	while (i < (size + 1))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*read_buffer(int fd, char *buffer, ssize_t *flagB)
{
	flagB = 0; // flags: ERR (-1) | EOF (0) | bytes (+)
	flagB = (ssize_t *)read(fd, buffer, BUFFER_SIZE);
	if (flagB <= 0)
		return(NULL);
	return (buffer);
}

char	*build_cache(int fd, char *cache) //calloc buffer & free buffer
{
	char	*buffer;
	ssize_t	flagB;

	buffer = ft_calloc(BUFFER_SIZE);
	buffer = read_buffer(fd, buffer, &flagB);
	cache = ft_strdup(buffer);
	free(buffer);
	return (cache);
}

char	*get_next_line(int fd)
{
	char *line;

	line = NULL;
	line = build_cache(fd, line);
	if (BUFFER_SIZE < 1 || fd < 0 || fd > MAX_FD)
		return (NULL);
	return(line);
}


int	main(void)//TODO: Implement argc, argv
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("t1.txt", O_RDONLY);
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(str != NULL);
	return (0);
}

