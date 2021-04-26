/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatreide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:22:24 by zatreide          #+#    #+#             */
/*   Updated: 2020/11/24 22:22:25 by zatreide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int i;

	if (n < 0)
	{
		ft_putchar_fd(45, fd);
		i = (unsigned int)(-n);
	}
	else
	{
		i = (unsigned int)n;
	}
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
	}
	ft_putchar_fd((char)(i % 10 + 48), fd);
}
