/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:38:17 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/11 22:19:55 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (0)
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> /* open() TODO:  REMOVER ANTES DE ENVIAR */
# include <stdio.h> /* open() TODO:  REMOVER ANTES DE ENVIAR */

char	*get_next_line(int fd);
int		ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
