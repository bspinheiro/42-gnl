#include "get_next_line.h"

char	*first_part_of(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (s[i] == 0)
	{
		return (NULL);
	}
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
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == 0)
	{
		free(s);
		return (NULL);
	}
	j = i;
	while (s[i] != '\0')
		i++;
	len = (i - j);
	str = ft_calloc(1, len);
	i = 0;
	j++;
	while (i < len)
	{
		str[i] = s[j];
		i++;
		j++;
	}
	free(s);
	return (str);
}

char	*get_content_of_file(int fd, char *backup)
{
	char	*temp;
	ssize_t	bytes;

	bytes = 1;
	while (bytes != 0 && !ft_strchr(backup, '\n'))
	{
		temp = calloc(1, (BUFFER_SIZE + 1));
		if (!temp)
			return (NULL);
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(temp);
			return (NULL);
		}
		backup = ft_strjoin(backup, temp);
		free(temp);
	}
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = get_content_of_file(fd, backup);
	if (!backup)
		return (NULL);
	line = first_part_of(backup);
	backup = second_part_of(backup);
	return (line);
}