/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:24:48 by cdapurif          #+#    #+#             */
/*   Updated: 2019/11/26 15:10:49 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_putnbr(long long nb)
{
	char c;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = (nb % 10 + 48);
	write(1, &c, 1);
}

void	ft_puthex(long long nb)
{
	char c;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 15)
		ft_puthex(nb / 16);
	if (nb % 16 > 9)
		c = (nb % 16 + 87);
	else
		c = (nb % 16 + 48);
	write(1, &c, 1);
}
