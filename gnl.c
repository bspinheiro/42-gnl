/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:47:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/15 20:40:03 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd, char *buffer, ssize_t *flag)
{
	// flags: ERR (-1) | EOF (0) | BYTES READ (+)
	*flag = read(fd, buffer, BUFFER_SIZE);
	if (*flag < 0)
		return (NULL);
	buffer[*flag] = 0;
	return (buffer);
}

char	*build_cache(int fd, char *cache, ssize_t *flag) //calloc buffer & free buffer
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buffer = read_buffer(fd, buffer, flag);
	//flag - buffer
	// > 0 - != \0  - loop join até \n e retorna resultado
	// < 0 - ==NULL - retorna o que ja tem
	// = 0 - ==\0   - 
	cache = ft_strdup(buffer);
	return (cache);
}

char	*get_next_line(int fd)
{
	char	*line;
	ssize_t	flag;

	line = NULL;
	flag = 0;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > MAX_FD)
		return (NULL);
	line = build_cache(fd, line, &flag);
	if (flag <= 0)
	{
		free(line);
		return (NULL);
	}
	return(line);
}


int	main(void)//TODO: Implement argc, argv
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("t2.txt", O_RDONLY);
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(str != NULL);
	return (0);
}

