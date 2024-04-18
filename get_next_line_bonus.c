/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:42 by ngoyat            #+#    #+#             */
/*   Updated: 2024/04/18 15:57:33 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// join and free
char	*ft_join(char *old_buffer, char *new_buffer)
{
	char	*temp;

	temp = ft_strjoin(old_buffer, new_buffer);
	if (!temp)
		return (free(old_buffer), NULL);
	free(old_buffer);
	old_buffer = temp;
	return (temp);
}

// delete line find
void	ft_update_buffer(char *buffer)
{
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = 0;
}

// take line for return
char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (free(line), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *old_buffer)
{
	char	*new_buffer;
	int		bytes_read;

	new_buffer = ft_join(NULL, old_buffer);
	if (!new_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(new_buffer, '\n'))
	{
		bytes_read = read(fd, old_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			old_buffer[0] = 0;
			return (NULL);
		}
		old_buffer[bytes_read] = '\0';
		new_buffer = ft_join(new_buffer, old_buffer);
		if (!new_buffer)
			return (NULL);
		if (ft_strchr(old_buffer, '\n'))
			break ;
	}
	if (ft_strlen(new_buffer) < 1)
		return (free(new_buffer), NULL);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*temp;

	if (read(fd, 0, 0) < 0)
	{
		buffer[0] = 0;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_file(fd, buffer[fd]);
	if (!temp)
		return (NULL);
	ft_update_buffer(buffer[fd]);
	return (temp);
}

//#include <stdio.h>
// int main(void)
// {
// 	char *line;

// 	line = get_next_line(0);
// 	while (line)
// 	{
// 		printf("MAIN: %s", line);
// 		free(line);
// 		line = get_next_line(0);
// 	}
// 	printf("%s", line);
// 	free(line);

// 	 return (0);
// }
