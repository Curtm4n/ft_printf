/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curtman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:11:40 by curtman           #+#    #+#             */
/*   Updated: 2019/12/03 20:46:48 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_zero(t_struct *data)
{
	if (!(data->flag & 2))
		place_sep(data, (data->flag & 8) ? data->width - 1 : data->width);
	if (data->flag & 8)
		write(1, "0", 1);
	if (data->flag & 2)
		place_sep(data, (data->flag & 8) ? data->width - 1 : data->width);
	data->nb_char += (data->flag & 8 && data->width == 0) ? 1 : data->width;
}

void	ft_print_octal(t_struct *d, va_list args)
{
	long long			len_oc;
	long long			len;
	unsigned long long	oct;

	oct = ft_u_resize(d, args);
	len_oc = ft_nblen_oc(oct);
	len = (len_oc > d->precision) ? len_oc : d->precision;
	len = (d->flag & 8 && oct != 0 && d->precision <= len_oc) ? len + 1 : len;
	if (d->precision > -1 && d->flag & 1)
		d->flag ^= 1;
	if (d->precision == 0 && oct == 0)
		return (ft_handle_zero(d));
	if (d->flag & 8 && oct != 0 && d->flag & 1 && d->precision <= len_oc)
		write(1, "0", 1);
	if (d->width > len && !(d->flag & 2))
		place_sep(d, d->width - len);
	if (d->flag & 8 && oct != 0 && !(d->flag & 1) && d->precision <= len_oc)
		write(1, "0", 1);
	place_precision(d->precision - len_oc);
	ft_putoct(oct);
	if (d->width > len && d->flag & 2)
		place_sep(d, d->width - len);
	d->nb_char += (len > d->width) ? len : d->width;
}
