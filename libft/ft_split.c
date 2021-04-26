/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:23:46 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:23:48 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			**clean(char **ar)
{
	size_t	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
	return (NULL);
}

static size_t		count_word(char const *s, char c)
{
	size_t	count;
	char	*str;

	str = (char *)s;
	count = 0;
	while (*str)
	{
		if (*str == c)
		{
			str++;
			continue ;
		}
		if (*str != c)
		{
			while (*str != c && *str)
				str++;
			count++;
		}
	}
	return (count);
}

static char			*trim_str(char *s, char c)
{
	char *str;

	str = s;
	while (*str == c && *str)
		str++;
	return (str);
}

static size_t		word_len(char const *s, char c)
{
	size_t	count;
	char	*str;

	str = (char *)s;
	count = 0;
	while (*str != c && *str)
	{
		count++;
		str++;
	}
	return (count);
}

char				**ft_split(char const *s, char c)
{
	char	*str;
	char	**buffer;
	size_t	word;
	size_t	i;
	size_t	j;

	i = -1;
	if (!s)
		return (NULL);
	str = (char *)s;
	word = count_word(str, c);
	if (!(buffer = malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	while (++i < word)
	{
		str = trim_str(str, c);
		if (!(buffer[i] = malloc(sizeof(char) * (word_len(str, c) + 1))))
			clean(buffer);
		j = 0;
		while (*str != c && *str != '\0')
			buffer[i][j++] = *str++;
		buffer[i][j] = '\0';
	}
	buffer[i] = NULL;
	return (buffer);
}
