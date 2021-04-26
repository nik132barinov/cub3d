/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:48:49 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:13:01 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t num)
{
	unsigned char *resource;
	unsigned char *destination;
	unsigned char symbol;

	symbol = (unsigned char)c;
	resource = (unsigned char*)src;
	destination = (unsigned char*)dst;
	if ((destination == 0) && (resource == 0))
	{
		return (0);
	}
	while (num--)
	{
		*destination = *resource;
		destination++;
		if ((*resource) == symbol)
		{
			return (destination);
		}
		resource++;
	}
	return (0);
}
