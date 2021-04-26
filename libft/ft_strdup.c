/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:28:56 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:28:57 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;
	char	*dst;

	len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	dst = s2;
	if (!s2)
	{
		return (0);
	}
	while (len--)
	{
		*dst = *s1;
		dst++;
		s1++;
	}
	*dst = '\0';
	return (s2);
}
