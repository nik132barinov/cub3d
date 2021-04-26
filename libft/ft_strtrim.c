/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 23:03:55 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 23:03:57 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;

	str = (char *)s1;
	if (!str || !set)
		return (0);
	while (*str && ft_strchr(set, *str))
		str++;
	len = ft_strlen(str);
	while (len && ft_strchr(set, str[len]))
		len--;
	return (ft_substr(str, 0, len + 1));
}
