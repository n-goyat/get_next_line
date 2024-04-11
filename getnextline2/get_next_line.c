/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:42 by ngoyat            #+#    #+#             */
/*   Updated: 2024/04/11 18:24:20 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// join and free
char	*ft_join(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	buffer = NULL;
	return (temp);
}

// delete line find
char	*ft_update(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i++;
	j = 0;
	// line == buffer
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	buffer = NULL;
	return (line);
}

// take line for return
char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	// malloc to eol
	// if (!ft_strchr(buffer, '\n'))
	line = ft_calloc(i + 1, sizeof(char));
	// else
	// 	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (free(line), NULL);
	i = 0;
	// line = buffer
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		bytes_read;

	if (!res)
		res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(res), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		buffer[bytes_read] = 0;
		res = ft_join(res, buffer);
		if (!res)
			return (free(buffer), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), buffer = NULL, res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	// error handling
	if (read(fd, 0, 0) < 0)
		return (buffer = NULL, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_file(fd, buffer);
	if (!temp)
		return (NULL);
//	free(buffer);
	buffer = temp;
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line || line[0] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_update(buffer);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;
// 	int		i;

// 	fd = open("text.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	i = 0;
// 	while (i < 7)
// 	{
// 		printf("output: %s", str);
// 		str = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*returned_line;
// 	int		i = 0;
// 	fd = open("text.txt", O_RDONLY);
// 	while (1)
// 	{
// 		returned_line = get_next_line(fd);
// 		if (!returned_line)
// 			break ;
// 		printf("Returned Line: %s\n", returned_line);
// 		i++;

// 		free(returned_line);
// 		returned_line = NULL;
// 	}
// 	return (0);
// }