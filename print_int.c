/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:03:51 by cdapurif          #+#    #+#             */
/*   Updated: 2019/11/30 01:11:09 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_int_next(t_struct *d, long long len, long long nbr)
{
	long long		cpy;
	long long		val_precision;
	unsigned short	f;
	char			sign;

	f = d->flag;
	sign = (f & 16) ? ' ' : '+';
	if (d->width > len && (!(f & 1) && !(f & 2)))
		place_sep(d, d->width - ((nbr < 0 || f & 4 || f & 16) ? len + 1 : len));
	if (nbr < 0 || f & 4 || f & 16)
		(nbr < 0) ? write(1, "-", 1) : write(1, &sign, 1);
	if (d->width > len && f & 1)
		place_sep(d, d->width - ((nbr < 0 || f & 4 || f & 16) ? len + 1 : len));
	val_precision = (f & 32) ? ft_nblen_commas(nbr) : ft_nblen(nbr);
	place_precision(d->precision - val_precision);
	cpy = (nbr < 0) ? -nbr : nbr;
	(f & 32) ? ft_putnbr_commas(cpy, 2) : ft_putnbr(cpy);
	if (d->width > len && f & 2)
		place_sep(d, d->width - ((nbr < 0 || f & 4 || f & 16) ? len + 1 : len));
}

void	ft_print_int(t_struct *d, va_list args)
{
	long long	len;
	long long	nbr;

	nbr = ft_resize(d, args);
	len = (d->flag & 32) ? ft_nblen_commas(nbr) : ft_nblen(nbr);
	len = (len > d->precision) ? len : d->precision;
	if (d->precision > -1 && d->flag & 1)
		d->flag ^= 1;
	if (d->precision == 0 && nbr == 0)
	{
		if (!(d->flag & 2))
			place_sep(d, (d->flag & 4) ? d->width - 1 : d->width);
		if (d->flag & 4)
			write(1, "+", 1);
		if (d->flag & 2)
			place_sep(d, (d->flag & 4) ? d->width - 1 : d->width);
		d->nb_char += ((d->flag & 4) && d->width == 0) ? 1 : d->width;
		return ;
	}
	ft_print_int_next(d, len, nbr);
	len = (nbr < 0 || d->flag & 4 || d->flag & 16) ? len + 1 : len;
	d->nb_char += (len > d->width) ? len : d->width;
}
