/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 00:28:22 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/25 00:28:24 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			size_n(int a)
{
	int size;
	int c;

	c = a;
	size = 1;
	if (a < 0)
		size++;
	while ((c /= 10) != 0)
		size++;
	return (size);
}

char				*ft_itoa(int a)
{
	char			*str;
	int				size;
	unsigned int	b;
	int				i;

	i = 0;
	size = size_n(a);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	str[size] = '\0';
	b = a;
	if (a < 0)
	{
		str[0] = '-';
		i = 1;
		b = -a;
	}
	while (--size >= i)
	{
		str[size] = b % 10 + '0';
		b /= 10;
	}
	return (str);
}
