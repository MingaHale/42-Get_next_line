#include "get_next_line_bonus.h"

char	*ft_new_left_str(char *keeper)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (keeper[i] && keeper[i] != '\n')
		i++;
	if (!keeper[i])
	{
		free(keeper);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(keeper) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (keeper[i])
		str[j++] = keeper[i++];
	str[j] = '\0';
	free(keeper);
	return (str);
}

char	*ft_get_line(char *keeper)
{
	int		i;
	char	*str;

	i = 0;
	if (!keeper[i])
		return (NULL);
	while (keeper[i] && keeper[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (keeper[i] && keeper[i] != '\n')
	{
		str[i] = keeper[i];
		i++;
	}
	if (keeper[i] == '\n')
	{
		str[i] = keeper[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read_to_left_str(int fd, char *keeper)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(keeper, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		keeper = ft_strjoin(keeper, buff);
	}
	free(buff);
	return (keeper);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*keeper[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	keeper[fd] = ft_read_to_left_str(fd, keeper[fd]);
	if (!keeper[fd])
		return (NULL);
	str = ft_get_line(keeper[fd]);
	keeper[fd] = ft_new_left_str(keeper[fd]);
	return (str);
}
// #include <stdio.h>
// int	main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *i;
// 	int fd2 = open("test2.txt", O_RDONLY);
// 	char *s;
// 	while(i || s)
// 	{
// 		i = get_next_line(fd);
// 		printf("%s", i);
// 		s = get_next_line(fd2);
// 		printf("%s", s);
// 	}
// }