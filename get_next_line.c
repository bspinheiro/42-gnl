/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:36:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/12 19:07:08 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd, int *flagEOF)
{
	char	*buffer;
	int		n;

	buffer = malloc (sizeof(char) * ((BUFFER_SIZE) + 1));
	if (!buffer)
		return (NULL);
	n = read(fd, buffer, BUFFER_SIZE);
	if (n < 0) // (-1) Erro de leitura do buffer
	{
		*flagEOF = -1;
		return (NULL);
	}
	if (n == 0) // (1) Fim do Arquivo
		*flagEOF = 1;
	buffer[n] = '\0';
	return (buffer);
}

char	*build_cache(int fd, char *cache)
{
	char	*buffer;
	int		flagEOF;

	flagEOF = 0; // Leitura Normal
	if (!cache)
	{//STRDUP ?
		cache = malloc(sizeof(char) * 1);
		cache[0] = '\0';
	}
	while (!ft_strchr(cache, '\n') || flagEOF == 0)
	{
		buffer = read_buffer(fd, &flagEOF);
		if (flagEOF != 0) // Em caso de Erro(-1) ou EOF(1)
		{
			free(buffer);
			break;
		}
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
	line = build_cache(fd, cache);
	if (ft_strchr(line, '\n'))
	{
		n = (ft_strchr(line,'\n') - line) + 1;

		temp = ft_strdup(line);
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
	}
	close(fd);
	return (0);
}

