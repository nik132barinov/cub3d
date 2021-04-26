/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:53:48 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:53:49 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char *resource;
	unsigned char *destination;

	resource = (unsigned char *)src;
	destination = (unsigned char *)dst;
	if (!dstsize || !dst)
	{
		if (!src)
			return (0);
		return (ft_strlen(src));
	}
	while (*resource != '\0' && --dstsize)
	{
		*destination = *resource;
		destination++;
		resource++;
	}
	*destination = '\0';
	return (ft_strlen(src));
}
