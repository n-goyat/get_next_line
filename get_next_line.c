/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:42 by ngoyat            #+#    #+#             */
/*   Updated: 2024/04/11 11:51:38 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = (char *)malloc(ft_strlen(s1) + 1);
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_storage(char *storage)
{
	char	*new_storage;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	if (!ptr)
	{
		new_storage = NULL;
		return (ft_free(&storage));
	}
	else
		len = (ptr - storage) + 1;
	if (!storage[len])
		return (ft_free(&storage));
	new_storage = ft_substr(storage, len, ft_strlen(storage) - len);
	ft_free(&storage);
	if (!new_storage)
		return (NULL);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*stash;
	int			bytes_read;
	char		*temp;
	int			len_newline;

	char *line; // extracted line
	line = NULL;
	if (!stash)
		stash = ft_strdup("");
	// if (!stash)
	// 	return (free(stash), stash = NULL, NULL);
	// if (stash && ft_strchr(stash, '\n'))
	// {
	// 	printf("stash %s\n", stash);
	// 	line = ft_substr(stash, 0, ft_strnlen(stash, '\n'));
	// 	temp = ft_substr(stash, ft_strnlen(line, '\0'), (ft_strnlen(stash,
	// 					'\0') - ft_strnlen(line, '\0')));
	// 	stash = temp;
	// 	free(temp);
	// 	// return (line);
	// }
	bytes_read = 0;
	while (bytes_read >= 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		stash = ft_strjoin(stash, buf);
		if (ft_strchr(stash, '\n'))
		{
			line = ft_substr(stash, 0, ft_strnlen(stash, '\n') + 1);
			temp = ft_substr(stash, ft_strnlen(line, '\0'), (ft_strnlen(stash,
							'\0') - ft_strnlen(line, '\0')));
			stash = temp;
			free(temp);
		}
		// len_newline = 0;
		// if (ft_strchr(stash, '\n'))
		// {
		// 	while (stash[len_newline] != '\n')
		// 		len_newline++;
		// 	line = line_extracter(stash, len_newline);
		// 	return (line);
		// 	// stash = ft_refresh(stash);
	}
	stash = clean_storage(stash);
	return (line);
}
// stash = ft_refresh(stash);


int	main(void)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (i < 4)
	{
		printf("output: %s", str);
		str = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}

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