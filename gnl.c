/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:47:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/16 03:32:57 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd, char *buffer, ssize_t *flag)
{
	// flags: (-2) ERR alloc | ERR read (-1) | EOF (0) | BYTES READ (+)
	*flag = read(fd, buffer, BUFFER_SIZE);
	if (*flag < 0)
		return (NULL);
	buffer[*flag] = 0;
	return (buffer);
}

char	*build_line(int fd, ssize_t *flag)
{
	static char		*cache;
	char			*buffer;
	char			*line;
	char			*temp;
	int				n;

	line =  NULL;
	n = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		*flag = -2;
		return (NULL);
	}
	while (*flag >= 0)
	{
		buffer = read_buffer(fd, buffer, flag);
		//fazer join da estática + consertar loop de saida /0 + memleaks
		if (!ft_strchr(buffer, '\n'))
			line = ft_strjoin(line, buffer);
		else
		{
			n = (ft_strchr(buffer, '\n') - buffer) + 1;
			temp = malloc(sizeof(char)*(n + 1));
			ft_memcpy(temp, buffer, n);
			temp[n] = '\0';
			line = ft_strjoin(line, temp);
			free(temp);
			cache= malloc(sizeof(char) * (n + 1));
			ft_memcpy(cache, buffer + n, n);
			cache[n] = 0;
			break;
		}
	}
	free(buffer);
	//flag - buffer
	// > 0 - != \0  - loop join até \n e retorna resultado
	// < 0 - ==NULL - retorna o que ja tem
	// = 0 - ==\0   - 
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	ssize_t		flag;

	line = NULL;
	flag = 0;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > MAX_FD)
		return (NULL);
	line = build_line(fd, &flag);
	if (flag < 0)
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

