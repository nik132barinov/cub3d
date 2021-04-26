/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:33:06 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:33:08 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t a;
	size_t b;
	size_t c;

	a = ft_strlen(dst);
	b = ft_strlen(src);
	c = 0;
	if (a >= dstsize)
		return (b + dstsize);
	while (src[c] && a + c + 1 < dstsize)
	{
		dst[a + c] = src[c];
		c++;
	}
	dst[a + c] = '\0';
	return (a + b);
}
