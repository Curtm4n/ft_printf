/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:15:34 by cdapurif          #+#    #+#             */
/*   Updated: 2020/01/22 12:07:53 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	ft_final_nbr(long double nbr, int exponant)
{
	if (exponant >= 0)
		nbr /= ft_recursive_power(10, exponant);
	else
		nbr *= ft_recursive_power(10, -exponant);
	return (nbr);
}

int			ft_find_exponant(t_struct *data, long double nbr)
{
	int			exponant;
	long double	cpy;

	cpy = nbr;
	exponant = 0;
	if (nbr == 0.0)
		return (exponant);
	while (((nbr < 0) ? (long long)-nbr : (long long)nbr) > 9)
	{
		nbr /= 10;
		exponant++;
	}
	while (((nbr < 0) ? (long long)-nbr : (long long)nbr) == 0)
	{
		nbr *= 10;
		exponant--;
	}
	cpy = ft_final_nbr(nbr, exponant);
	cpy = ft_round_nbr(data, nbr);
	if ((long)cpy == 10 || (long)cpy == -10)
	{
		cpy /= 10;
		exponant++;
	}
	return (exponant);
}

void		ft_write_e(t_struct *data, long double nbr)
{
	long long	rounding;
	long double	cpy;

	nbr = (nbr < 0) ? -nbr : nbr;
	ft_putnbr((long long)nbr);
	nbr -= (long long)nbr;
	if (data->precision == 0)
	{
		if (data->flag & 8)
			write(1, ".", 1);
		return ;
	}
	write(1, ".", 1);
	rounding = (data->precision >= 0) ? data->precision : 6;
	cpy = nbr * 10;
	nbr *= ft_recursive_power(10, rounding);
	while ((int)cpy == 0 && rounding > 1)
	{
		write(1, "0", 1);
		cpy *= 10;
		rounding--;
	}
	ft_putnbr(nbr);
}

void		ft_print_e_next(t_struct *d, long long len, long double nbr, int e)
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
	ft_write_e(d, nbr);
	(e < 0) ? write(1, "e-", 2) : write(1, "e+", 2);
	if (((e < 0) ? -e : e) < 10)
		write(1, "0", 1);
	ft_putnbr(((e < 0) ? -e : e));
	if (d->width > len && f & 2)
		place_sep(d, d->width - ((f & 8 && p == 0) ? len + 1 : len));
}

void		ft_print_e(t_struct *data, va_list args)
{
	int			exponant;
	long double nbr;
	long long	len;

	nbr = (data->size & L) ? va_arg(args, long double) : va_arg(args, double);
	len = 5;
	if (data->precision != 0)
		len = len + ((data->precision < 0) ? 6 : data->precision) + 1;
	len = (nbr < 0 || data->flag & 4 || data->flag & 16) ? len + 1 : len;
	exponant = ft_find_exponant(data, nbr);
	nbr = ft_final_nbr(nbr, exponant);
	nbr = ft_round_nbr(data, nbr);
	ft_print_e_next(data, len, nbr, exponant);
	len = (data->precision == 0 && data->flag & 8) ? len + 1 : len;
	len = (data->width > len) ? data->width : len;
	data->nb_char += len;
}
