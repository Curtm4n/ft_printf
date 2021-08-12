/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:34:33 by cdapurif          #+#    #+#             */
/*   Updated: 2019/11/30 01:14:20 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_uint(t_struct *data, va_list args)
{
	long long			val_pre;
	long long			len;
	unsigned long long	nbr;

	nbr = ft_u_resize(data, args);
	len = (data->flag & 32) ? ft_u_nblen_commas(nbr) : ft_u_nblen(nbr);
	len = (len > data->precision) ? len : data->precision;
	if (data->precision > -1 && data->flag & ZERO)
		data->flag ^= ZERO;
	if (data->precision == 0 && nbr == 0)
	{
		place_sep(data, data->width);
		data->nb_char += data->width;
		return ;
	}
	if (data->width > len && !(data->flag & MINUS))
		place_sep(data, data->width - len);
	val_pre = (data->flag & 32) ? ft_u_nblen_commas(nbr) : ft_u_nblen(nbr);
	place_precision(data->precision - val_pre);
	(data->flag & 32) ? ft_putnbr_commas(nbr, 2) : ft_putnbr(nbr);
	if (data->width > len && data->flag & MINUS)
		place_sep(data, data->width - len);
	data->nb_char += (len > data->width) ? len : data->width;
}
