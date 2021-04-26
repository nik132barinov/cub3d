/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:09:43 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:10:07 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	char *digits;
	char *character;

	digits = "1234567890";
	character = digits;
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
