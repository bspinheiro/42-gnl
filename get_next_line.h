/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-silv <bda-silv@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:38:17 by bda-silv          #+#    #+#             */
/*   Updated: 2022/07/21 04:40:45 by bda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (1) /* TODO: set 1 for evaluation*/
# endif

# define MAX_FD (256) /* FD limit in macOS: ulimit -Sn */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> /* open() TODO:  REMOVER ANTES DE ENVIAR */
# include <stdio.h> /* open() TODO:  REMOVER ANTES DE ENVIAR */

char	*get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char *s, int start, int len);

#endif
