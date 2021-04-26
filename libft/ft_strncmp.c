/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:57:07 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:57:08 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t num)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (num == 0)
	{
		return (0);
	}
	if (!num && !s1)
	{
		return (0);
	}
	while ((*str1 == *str2) && (--num) && (*str1 != '\0') && (*str2 !=
	'\0'))
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
