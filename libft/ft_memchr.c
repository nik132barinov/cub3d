/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:14:59 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:15:03 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ptr;
	unsigned char *findcharacter;

	ptr = (unsigned char*)s;
	findcharacter = 0;
	while (n--)
	{
		if ((*ptr) != (unsigned char)c)
		{
			ptr++;
		}
		else
		{
			findcharacter = ptr;
			break ;
		}
	}
	return (findcharacter);
}
