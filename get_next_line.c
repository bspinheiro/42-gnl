# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> /* open() TODO:  REMOVER ANTES DE ENVIAR */
# include <stdio.h> /* open() TODO:  REMOVER ANTES DE ENVIAR */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (1) /* TODO: set 1 for evaluation*/
# endif

# ifndef MAX_FD
#  define MAX_FD (256) /* TODO: set 1 for evaluation*/
# endif

char	*get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char *s, int start, int len);

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*str;

	if (!s1)
	{
		s1 = malloc (sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, l1);
	ft_memcpy(str + l1, s2, l2);
	str[l1 + l2] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (((char *)dst) == ((char *)src) && n > 0)
		return (0);
	else
	{
		while (i < n)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
		return (dst);
	}
}

char	*ft_strdup(char *s)
{
	size_t	l;
	char	*t;

	l = ft_strlen((char *)s);
	t = malloc(sizeof(char) * (l + 1));
	if (t == NULL)
		return (NULL);
	ft_memcpy(t, s, l);
	t[l] = '\0';
	return (t);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = 0;
	return (str);
}

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

char	*first_part_of(char *cache)
{
	int		n;
	char	*line;
		
	n = 0;
	n = (ft_strchr(cache, '\n') - cache) + 1;
	if (n < 0)
		return (NULL);
	line = ft_substr(cache, 0, n);
	return(line);
}

char	*second_part_of(char *cache)
{
	int		n;
	char	*temp;

	n = 0;
	n = (ft_strchr(cache, '\n') - cache) + 1;
	if (n < 0)
		free(cache);
		return (NULL);
	temp = ft_substr(cache, n, ft_strlen(cache) + 1);
	return (temp);
}

char	*build_line(int fd, char *cache)
{
	ssize_t flag;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer) 
		return (NULL);
	flag = 1;
	while (flag > 0 && !ft_strchr(cache, '\n'))
	{
		flag = read(fd, buffer, BUFFER_SIZE);
		if (flag < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[flag] = '\0';
		cache = ft_strjoin(cache, buffer);
	}
	free(buffer);
	buffer = NULL;
	return (cache);
}
	
char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > MAX_FD)
		return (NULL);
	cache = build_line(fd, cache);
	if (!cache)
		return (NULL);	
	line = first_part_of(cache);
	cache = second_part_of(cache);
	return (line);
}

int	main(void)//TODO: Implement argc, argv
{
	int		fd;
	char	*str;


	str = NULL;
	//fd = open("gnlTester/files/41_with_nl", O_RDONLY);
    fd = open("arquivo.txt", O_RDONLY);

    str = get_next_line(fd);
    printf("%s", str);
    free(str);

    str = get_next_line(fd);
    printf("%s", str);
    free(str);

    /*
	do
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	} while(str != NULL);
    */
	return (0);
}

