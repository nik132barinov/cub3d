/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 23:08:17 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 23:08:19 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str || !s)
		return (0);
	if (start >= ft_strlen(s))
		return (str);
	while (i < len && *(s + start + 1))
	{
		*(str + i) = *(s + start + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
