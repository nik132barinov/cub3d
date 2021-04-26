/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:48:49 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/06 19:49:00 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *resource;
	unsigned char *destination;

	resource = (unsigned char *)src;
	destination = (unsigned char *)dst;
	if ((resource == 0) && (destination == 0))
		return (0);
	if (destination < resource)
	{
		while (len--)
		{
			*destination++ = *resource++;
		}
	}
	else
	{
		resource = resource + len;
		destination = destination + len;
		while (len--)
		{
			*--destination = *--resource;
		}
	}
	return (dst);
}
