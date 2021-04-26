/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:47:40 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:01:23 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	char *alphabet;
	char *character;

	alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
	character = alphabet;
	while (*character != '\0' && *character != c)
	{
		++character;
	}
	if (*character)
	{
		return (1);
	}
	return (0);
}
