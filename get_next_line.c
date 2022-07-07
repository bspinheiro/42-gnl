/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:36:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/07 17:01:50 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
- Loop do read até \n
- cache >>> free;
*/

#include "get_next_line.h"

int	mdc(int a, int b)
{
	int remainder;
	while (remainder != 0)
	{
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return (a);
}

static char	*bet_next_line(int fd)
{
	int		n;
	int		i;
	int		mdc_;
	char	*buffer;
	static char	*cache;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (!buffer)
		return (NULL);
	if (!cache)
		cache = malloc(sizeof(char) * 1);
	i = 0;
	n = 1;
	while (n > 0 && !ft_strchr(cache, '\n'))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (ft_strchr(cache, '\n'))
			return (ft_strchr(cache, '\n'));
		if (n <= 0)
			return (NULL);
		buffer[n] = '\0';
		cache = ft_strjoin(cache, buffer);
	}
	free(buffer);
	return (cache);
}

char	*basics(int fd)
{
	char *buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	read(fd, buffer, BUFFER_SIZE);
	return (buffer);
}

int	main(void)
{
	int fd;
	char *str;

	fd = open("teste.txt", O_RDONLY);
	str = bet_next_line(fd);
	printf("%s",str);
	return (0);
}
