/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:17:45 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:17:48 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t num)
{
	unsigned char *str1;
	unsigned char *str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (num == 0)
	{
		return (0);
	}
	while ((*str1 == *str2) && (--num))
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
