/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:36:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/08 18:29:16 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
- Loop do read até \n >> Salvar \n
- Cache >>> free;
- Main com argc **argv
*/

#include "get_next_line.h"

char	*bet_next_line(int fd)
{
	int			n;
	int			i;
	char		*buffer;
	char		*temp;
	static char	*cache;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (!buffer)
		return (NULL);
	if (!cache)
		cache = malloc(sizeof(char) * 1);
	n = 0;
	while (!ft_strchr(cache, '\n'))
	{
		puts("1");
		n = read(fd, buffer, BUFFER_SIZE);
		puts("2");
		if (n <= 0)
			break;
		buffer[n] = '\0';
		cache = ft_strjoin(cache, buffer);
		printf("buffer: %s cache: %s \n", buffer, cache);
	}
	i = 0;
	if (ft_strchr(cache, '\n'))
	{
		temp = malloc(sizeof(char) * 1);
		while (ft_strchr(cache, '\n'))
		{
			temp[i] = cache[i];
			i++;
		}
		temp[i] = '\0';
		cache = ft_strdup(temp);
	}

	//TODO: funcao que pega a linha a ser impressa.
	//TODO: funcao tratar a sobra a ser guardada;
	//TODO: checar \n e \0 (tratar tb na saida)
	return (cache);
}

int	main(void)
{
	int fd;
	char *str;

	fd = open("teste.txt", O_RDONLY);
	str = bet_next_line(fd);
	printf("%s-\n",str);
	return (0);
}
