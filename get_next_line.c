/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:47:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/21 04:50:54 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

char	*read_buffer(int fd, char *buffer, ssize_t *flag)
{
	*flag = read(fd, buffer, BUFFER_SIZE);
	if (*flag < 0)
		return (NULL);
	buffer[*flag] = 0;
	return (buffer);
}

char	*build_line(int fd, ssize_t *flag)
{
	char	*buffer;
	char	*line;

	line = ft_strdup("\0");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		*flag = -2;
		return (NULL);
	}
	while (*flag > 0 && !ft_strchr(line, '\n'))
	{
		buffer = read_buffer(fd, buffer, flag);
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*cut_n_save(char *temp, char **cache)
{
	int		n;
	char	*line;
	char	*tmp;

	n = 0;
	if (!temp)
		return (NULL);
	if (ft_strlen(*cache) != 0)
		tmp = ft_strjoin(*cache, temp);
	else
		tmp = ft_strdup(temp);
	n = (ft_strchr(tmp, '\n') - tmp) + 1;
	line = ft_substr(tmp, 0, n);
	*cache = ft_substr(tmp, n, ft_strlen(tmp) + 1);
	if (*temp)
		free(temp);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*temp;
	char		*line;
	ssize_t		flag;

	temp = NULL;
	flag = 1;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > MAX_FD)
		return (NULL);
	if (!cache)
		cache = ft_strdup("\0");
	if (!ft_strchr(cache, '\n'))
	{
		temp = build_line(fd, &flag);
		line = cut_n_save(temp, &cache);
	}
	else
		line = cut_n_save("", &cache);
	return (line);
}

int	main(void)//TODO: Implement argc, argv
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("t4.txt", O_RDONLY);
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(str != NULL);
	return (0);
}
