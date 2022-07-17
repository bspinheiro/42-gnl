/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:47:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/17 20:06:02 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void *ft_calloc(size_t size)
{
	size_t *ptr;
	size_t i;

	i = 0;
	ptr = malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	else
		while(i < size + 1)
		{
			ptr[i] = 0;
			i++;
		}
	return (ptr);
}

char	*read_buffer(int fd, char *buffer, ssize_t *flag)
{
	// flags: (-2) ERR alloc | ERR read (-1) | EOF (0) | BYTES READ (+)
	*flag = read(fd, buffer, BUFFER_SIZE);
	if (*flag < 0)
		return (NULL);
	buffer[*flag] = 0;
	return (buffer);
}

int		n_counter(char *str)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			n++;
		i++;
	}
	return (n);
}

char	*build_line(int fd, ssize_t *flag)
{
	static char		*cache;
	char			*buffer;
	char			*line;
	char			*tmp;
	int				n;
	int				n_total;
	//fazer join da estática + consertar loop de saida /0 + memleaks
	//flag - buffer
	// > 0 - != \0  - loop join até \n e retorna resultado
	// < 0 - ==NULL - retorna o que ja tem
	// = 0 - ==\0   -
	n = 0;
	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		*flag = -2;
		return (NULL);
	}
	while (*flag > 0)
	{
		buffer = read_buffer(fd, buffer, flag);
//		printf("-*--buffer:%p-%s-%d-\n", buffer, buffer, ft_strlen(buffer));
		if (ft_strlen(cache) != 0)
		{
			line = ft_strjoin(line, cache);
			free(cache);
			cache = NULL;
		}
		if (!ft_strchr(buffer, '\n'))
		{
			line = ft_strjoin(line, buffer);
//			printf("-A--line:%p-%s-%d-\n", line, line, ft_strlen(line));
		}
		else
		{
			n = (ft_strchr(buffer, '\n') - buffer) + 1;
//			printf("-N--n:%i---\n", n);
			tmp = ft_calloc(n);
			//temp = malloc(sizeof(char)*(n + 1));
			//temp[n] = '\0';
			ft_memmove(tmp, buffer, n);
//			printf("-B--temp:%p-%s-%d-\n", temp, temp, ft_strlen(temp));
			line = ft_strjoin(line, tmp);
			//free(temp);
			cache = ft_calloc(BUFFER_SIZE + 1);
			//cache = malloc(sizeof(char) * (BUFFER_SIZE + 1));
			ft_memmove(cache, buffer + n, (ft_strlen(buffer) - n));
			//cache[n] = 0;
//			printf("-C--cache:%p-%s-%d-\n", cache, cache, ft_strlen(cache));
			free(tmp);
			break;
		}
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	ssize_t		flag;

	line = NULL;
	flag = 1;
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
	fd = open("t4.txt", O_RDONLY);
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(*str);
	return (0);
}
