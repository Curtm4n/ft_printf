/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curtman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:11:58 by curtman           #+#    #+#             */
/*   Updated: 2019/12/04 16:06:41 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		ft_recursive_power(long long nbr, long long power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (nbr);
	if (power > 1)
		nbr *= ft_recursive_power(10, --power);
	return (nbr);
}

long double		ft_round_nbr(t_struct *data, long double nbr)
{
	long long	rounding;

	rounding = (data->precision >= 0) ? data->precision : 6;
	rounding = ft_recursive_power(10, rounding);
	nbr *= rounding;
	nbr += (nbr < 0) ? -0.5 : 0.5;
	return (nbr / rounding);
}

void			ft_write_float(t_struct *data, long double nbr)
{
	long long	ipart;
	long long	rounding;
	long double	fpart;
	long double	cpy;

	ipart = ((nbr < 0) ? (long long)-nbr : (long long)nbr);
	fpart = ((nbr < 0) ? (long double)-nbr : (long double)nbr) - ipart;
	ft_putnbr(ipart);
	if (data->precision == 0)
	{
		if (data->flag & 8)
			write(1, ".", 1);
		return ;
	}
	write(1, ".", 1);
	rounding = (data->precision >= 0) ? data->precision : 6;
	cpy = fpart * 10;
	fpart *= ft_recursive_power(10, rounding);
	while ((int)cpy == 0 && rounding > 1)
	{
		write(1, "0", 1);
		cpy *= 10;
		rounding--;
	}
	ft_putnbr(fpart);
}

void			ft_print_float_next(t_struct *d, long long len, long double nbr)
{
	char			sign;
	unsigned short	f;
	long long		p;

	f = d->flag;
	p = d->precision;
	sign = (f & 16) ? ' ' : '+';
	if (d->width > len && (!(f & 1) && !(f & 2)))
		place_sep(d, d->width - ((f & 8 && p == 0) ? len + 1 : len));
	if (nbr < 0 || f & 4 || f & 16)
		(nbr < 0) ? write(1, "-", 1) : write(1, &sign, 1);
	if (d->width > len && f & 1)
		place_sep(d, d->width - ((f & 8 && p == 0) ? len + 1 : len));
	ft_write_float(d, nbr);
	if (d->width > len && f & 2)
		place_sep(d, d->width - ((f & 8 && p == 0) ? len + 1 : len));
}

void			ft_print_float(t_struct *d, va_list args)
{
	long double		nbr;
	long long		len;

	nbr = (d->size & L) ? va_arg(args, long double) : va_arg(args, double);
	len = ft_nblen(((nbr < 0) ? (long long)-nbr : (long long)nbr));
	if (d->precision != 0)
		len = len + ((d->precision < 0) ? 6 : d->precision) + 1;
	len = (nbr < 0 || d->flag & 4 || d->flag & 16) ? len + 1 : len;
	nbr = ft_round_nbr(d, nbr);
	ft_print_float_next(d, len, nbr);
	len = (d->precision == 0 && d->flag & 8) ? len + 1 : len;
	len = (d->width > len) ? d->width : len;
	d->nb_char += len;
}
