/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:23:06 by cdapurif          #+#    #+#             */
/*   Updated: 2020/02/17 16:55:22 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	resize_char(t_struct *data, va_list args)
{
	wint_t	c;

	if (data->size == 1)
		c = (unsigned short)va_arg(args, int);
	if (data->size == 3)
		c = (unsigned char)va_arg(args, int);
	if (data->size > 3 && data->size < 8)
		c = (wint_t)va_arg(args, wint_t);
	if (data->size > 7)
		c = va_arg(args, unsigned long long);
	if (data->size == 0)
		c = (char)va_arg(args, int);
	return (c);
}

void				ft_print_c(t_struct *data, va_list args)
{
	long long	len;
	long long	c;

	c = resize_char(data, args);
	if (data->size > 3 && data->size < 8 && (c < 0 || c > 255))
	{
		data->nb_char = -1;
		return ;
	}
	len = (data->width < 1) ? 1 : data->width;
	if (!(data->flag & MINUS))
		place_sep(data, len - 1);
	write(1, &c, 1);
	if (data->flag & MINUS)
		place_sep(data, len - 1);
	data->nb_char += len;
}
