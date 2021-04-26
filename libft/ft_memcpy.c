/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:48:49 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/06 19:49:00 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				*ft_memcpy(void *dest, const void *src, size_t num)
{
	const char	*resource;
	char		*destination;

	resource = (const char *)src;
	destination = (char *)dest;
	if ((destination == 0) && (resource == 0))
	{
		return (0);
	}
	while (num)
	{
		*destination = *resource;
		destination++;
		resource++;
		--num;
	}
	return (dest);
}
