/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 23:00:36 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 23:00:37 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	size_t len;

	len = ft_strlen(s);
	if ((char)c == '\0')
	{
		return ((char*)s + len);
	}
	while (len--)
	{
		if (*(s + len) == (char)c)
			return ((char *)s + len);
	}
	return (0);
}
