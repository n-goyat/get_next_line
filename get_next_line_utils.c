/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoyat <ngoyat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:48:21 by ngoyat            #+#    #+#             */
/*   Updated: 2024/04/16 17:52:49 by ngoyat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*res;
	int		i;
	int		j;
	int		k;

	k = 0;
	while (s2[k] != '\0' && s2[k] != '\n')
		k++;
	k += (s2[k] == '\n');
	len = ft_strlen(s1) + k;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res || !s2)
		return (NULL);
	i = 0;
	if (s1 && i-- >= 0)
		while (s1[++i] != 0)
			res[i] = s1[i];
	j = 0;
	while (j < k)
		res[i++] = s2[j++];
	res[len] = 0;
	return (res);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	if (!str)
		return ;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;

	res = malloc(count * size);
	if (!res)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
