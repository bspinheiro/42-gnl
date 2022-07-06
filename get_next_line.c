/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:36:50 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/06 19:54:01 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

*/

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		n;
	int		i;
	char	*buffer;
	char	*cache;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	buffer[BUFFER_SIZE] = '\0';
	n = read(fd, buffer, BUFFER_SIZE);
/*	printf("%i\n", n);
	i = 0;
	while (buffer[i] != '\n' || buffer[i] != '\0')
	{
		ft_strjoin(cache, buffer);
		i++;
	}
*/
	return (buffer);
}

int	main(void)
{
	int fd;
	char *str;

	fd = open("teste.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s",str);
	return (0);
}
