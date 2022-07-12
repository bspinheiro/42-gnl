/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:36:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/12 03:59:28 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd, int *n)
{
	char	*buffer;

	buffer = malloc (sizeof(char) * ((BUFFER_SIZE) + 1));
	if (!buffer)
		return (NULL);
	*n = read(fd, buffer, BUFFER_SIZE);
	if (*n < 0)
	{
		return (NULL);
	}
	buffer[*n] = '\0';
	return (buffer);
}

char	*build_cache(int fd, char *cache)
{
	char	*buffer;
	int		n;

	n = 1;
	if (!cache)
	{
		cache = malloc(sizeof(char) * 1);
		cache[0] = '\0';
	}
	while (n > 0)
	{
		buffer = read_buffer(fd, &n);
		if (n < 0)
			return (NULL);
		cache = ft_strjoin(cache, buffer);
	}
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;
	char		*temp;
	int			n;

	if (BUFFER_SIZE < 1 || fd < 0)
	{
		if (cache)
			free(cache);
		return (NULL);
	}
	n = 0;
	line = build_cache(fd, cache);
	if (ft_strchr(line, '\n') != -1)
	{
		temp = ft_strdup(line);

		n = ft_strchr(line, '\n');
		free(line);
		line = malloc(sizeof(char) * (n + 1));
		ft_memcpy(line, temp, n);
		line[n] = '\0';
		if ((ft_strlen(temp) - ft_strlen(line)) != 0)
		{
			//free(cache);
			cache = ft_strdup(temp + n);
		}
		free(temp);
	}
	return(line);
}

/*
int	main(void)//TODO: Implement argc, argv
{
	int fd;
	char *str;

	fd = open("teste.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!*str)
			break ;
		printf("%s",str);
		free(str);
	}// while (!*str);
	close(fd);
	return (0);
}
*/
