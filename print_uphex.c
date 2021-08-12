/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uphex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:57:47 by cdapurif          #+#    #+#             */
/*   Updated: 2019/11/27 17:00:46 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_uphex(unsigned long long nb)
{
	char c;

	if (nb > 15)
		ft_put_uphex(nb / 16);
	if (nb % 16 > 9)
		c = (nb % 16 + 55);
	else
		c = (nb % 16 + 48);
	write(1, &c, 1);
}

void	ft_print_uphex(t_struct *d, va_list args)
{
	long long			len;
	unsigned long long	hex;

	hex = ft_u_resize(d, args);
	len = (ft_nblen_hex(hex) > d->precision) ? ft_nblen_hex(hex) : d->precision;
	len = (d->flag & 8 && hex != 0) ? len + 2 : len;
	if (d->precision > -1 && d->flag & 1)
		d->flag ^= 1;
	if (d->precision == 0 && hex == 0)
	{
		place_sep(d, d->width);
		d->nb_char += d->width;
		return ;
	}
	if (d->flag & 8 && hex != 0 && d->flag & 1)
		write(1, "0X", 2);
	if (d->width > len && !(d->flag & 2))
		place_sep(d, d->width - len);
	if (d->flag & 8 && hex != 0 && !(d->flag & 1))
		write(1, "0X", 2);
	place_precision(d->precision - ft_nblen_hex(hex));
	ft_put_uphex(hex);
	if (d->width > len && d->flag & 2)
		place_sep(d, d->width - len);
	d->nb_char += (len > d->width) ? len : d->width;
}
