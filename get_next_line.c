/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:16:53 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/22 09:24:15 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*first_part_of(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (s[i] == 0)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	str = ft_calloc(1, (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		str[i] = '\n';
	return (str);
}

char	*second_part_of(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	if (s[i] == 0)
	{
		free(s);
		return (NULL);
	}
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	j = i;
	while (s[i] != '\0')
		i++;
	len = (i - j);
	str = ft_calloc(1, len);
	i = 0;
	j++;
	while (i < len)
		str[i++] = s[j++];
	free(s);
	return (str);
}

char	*build_line(int fd, char *cache)
{
	char	*buffer;
	ssize_t	bytes;

	bytes = 1;
	while (bytes != 0 && !ft_strchr(cache, '\n'))
	{
		buffer = ft_calloc(1, (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		cache = ft_strjoin(cache, buffer);
		free(buffer);
	}
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cache = build_line(fd, cache);
	if (!cache)
		return (NULL);
	line = first_part_of(cache);
	cache = second_part_of(cache);
	return (line);
}
/*
int	main(void)//TODO: Implement argc, argv
{
	int		fd;
	char	*str;

	str = NULL;
	//fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	fd = open("arquivo.txt", O_RDONLY);
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(str != NULL);
	return (0);
}
*/
