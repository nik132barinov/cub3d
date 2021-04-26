/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:28:26 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:28:28 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int character)
{
	char i;

	i = *string;
	if ((char)character == '\0')
	{
		return ((char *)string + ft_strlen(string));
	}
	while (i)
	{
		if (*string == (char)character)
		{
			return (char *)string;
		}
		else if (!*string)
		{
			break ;
		}
		string++;
	}
	return (0);
}
