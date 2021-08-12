/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:12:59 by cdapurif          #+#    #+#             */
/*   Updated: 2021/08/12 18:58:42 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	ft_u_nblen(unsigned long long nbr)
{
	int i;

	i = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

long long			ft_nblen_hex(unsigned long long hex)
{
	int i;

	i = 1;
	while (hex > 15)
	{
		hex /= 16;
		i++;
	}
	return (i);
}

const char			*ft_handle_percent(const char *format, t_struct *data)
{
	if (data->width > 1 && data->flag != 2)
		place_sep(data, data->width - 1);
	write(1, "%", 1);
	if (data->width > 1 && data->flag == 2)
		place_sep(data, data->width - 1);
	data->nb_char += (data->width > 1) ? data->width : 1;
	format++;
	return (format);
}

long long			ft_resize(t_struct *data, va_list args)
{
	if (data->size == 1)
		return ((long long)(short)va_arg(args, int));
	if (data->size == 3)
		return ((long long)(char)va_arg(args, int));
	if (data->size > 3 && data->size < 8)
		return ((long long)(long)va_arg(args, long));
	if (data->size > 7)
		return ((long long)va_arg(args, long long));
	return ((long long)va_arg(args, int));
}

unsigned long long	ft_u_resize(t_struct *data, va_list args)
{
	if (data->size == 1)
		return ((unsigned long long)(unsigned short)va_arg(args, unsigned int));
	if (data->size == 3)
		return ((unsigned long long)(unsigned char)va_arg(args, unsigned int));
	if (data->size > 3 && data->size < 8)
		return ((unsigned long long)(unsigned long)va_arg(args, unsigned long));
	if (data->size > 7)
		return ((unsigned long long)va_arg(args, unsigned long long));
	return ((unsigned long long)va_arg(args, unsigned int));
}
