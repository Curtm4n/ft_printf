/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curtman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:04:05 by curtman           #+#    #+#             */
/*   Updated: 2020/02/06 11:39:03 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_remove_zeros(t_struct *data, long double nbr)
{
	int			indicator;
	long long	prec;

	indicator = 0;
	prec = data->precision + 1;
	while (--prec > 0)
	{
		nbr -= (long long)nbr;
		nbr *= 10;
		if ((long long)nbr == 0)
			indicator++;
		else
			indicator = 0;
	}
	data->precision -= indicator;
	if (data->precision < 0)
		data->precision = 0;
}

long long	ft_exponant(t_struct *data, long double nbr, long long len, int exp)
{
	data->precision -= 1;
	exp = ft_find_exponant(data, nbr);
	nbr = ft_final_nbr(nbr, exp);
	nbr = ft_round_nbr(data, nbr);
	ft_remove_zeros(data, nbr);
	len = 5 + data->precision;
	len += (data->precision > 0) ? 1 : 0;
	len = (nbr < 0 || data->flag & 4 || data->flag & 16) ? len + 1 : len;
	ft_print_e_next(data, len, nbr, exp);
	return (len);
}

long long	ft_float(t_struct *data, long double nbr, long long len, int exp)
{
	data->precision -= (exp + 1);
	nbr = ft_round_nbr(data, nbr);
	if (!(data->flag & 8))
		ft_remove_zeros(data, nbr);
	len = ft_nblen((long long)nbr);
	len = len + data->precision;
	len += (data->precision > 0) ? 1 : 0;
	len = (nbr < 0 || data->flag & 4 || data->flag & 16) ? len + 1 : len;
	ft_print_float_next(data, len, nbr);
	return (len);
}

void		ft_condition(t_struct *data, long double nbr, int exponant)
{
	long long	len;

	len = 0;
	if (exponant < -4 || exponant >= data->precision)
		len = ft_exponant(data, nbr, len, exponant);
	else
		len = ft_float(data, nbr, len, exponant);
	len = (data->width > len) ? data->width : len;
	data->nb_char += len;
}

void		ft_print_g(t_struct *data, va_list args)
{
	long double nbr;
	int			exponant;

	data->precision = (data->precision < 0) ? 6 : data->precision;
	data->precision = (data->precision == 0) ? 1 : data->precision;
	nbr = (data->size & L) ? va_arg(args, long double) : va_arg(args, double);
	exponant = ft_find_exponant(data, nbr);
	ft_condition(data, nbr, exponant);
}
